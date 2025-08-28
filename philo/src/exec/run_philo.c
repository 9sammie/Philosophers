/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:19:38 by maballet          #+#    #+#             */
/*   Updated: 2025/08/28 19:12:57 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*monitor_routine(t_philo *philo)
{
	
}

int	hold_your_horses(t_philo *philo)
{
	pthread_mutex_lock(&philo->room->m_printing);
	while (!philo->room->time_to_start)
	{
		pthread_mutex_unlock(&philo->room->m_printing);
		usleep(100);
		pthread_mutex_lock(&philo->room->m_printing);
	}
	usleep(100);
	pthread_mutex_unlock(&philo->room->m_printing);
	pthread_mutex_lock(&philo->m_last_t_eaten);
	philo->last_t_eaten = get_time_in_milliseconds();
	if (philo->last_t_eaten == ERR_GETTIMEOFDAY)
		return (ERR_GETTIMEOFDAY);
	pthread_mutex_unlock(&philo->m_last_t_eaten);
	return (ALL_OK);
}

static void	take_forks(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->main_fork->m_available);
		if (!philo->main_fork->available)
		{
			pthread_mutex_unlock(&philo->main_fork->m_available);
            usleep(100);
            continue;
		}
		philo->main_fork->available = false;
		pthread_mutex_unlock(&philo->main_fork->m_available);
		pthread_mutex_lock(&philo->side_fork->m_available);
		if (!philo->side_fork->available)
		{
		    pthread_mutex_lock(&philo->main_fork->m_available);
            philo->main_fork->available = true;
            pthread_mutex_unlock(&philo->main_fork->m_available);
            pthread_mutex_unlock(&philo->side_fork->m_available);
			usleep(100);
			continue;
		}
		philo->side_fork->available = false;
		pthread_mutex_unlock(&philo->side_fork->m_available);
		break;
	}
}

static void	put_down_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->main_fork->m_available);
	philo->main_fork->available = true;
	pthread_mutex_unlock(&philo->main_fork->m_available);
	pthread_mutex_lock(&philo->side_fork->m_available);
	philo->side_fork->available = true;
	pthread_mutex_unlock(&philo->side_fork->m_available);
}

void	odd_even_departure(t_philo *philo)
{
	if (philo->room->philo_nbr % 2 == 0)
	{
		if (philo->parity == 0)
			usleep(philo->t_eat/2);
	}
	else
	{
		if (philo->id % 3 > 0)
			usleep((philo->id % 3) * (philo->t_eat / 3));
	}
}

static void	*philo_routine(void *arg)
{
	(void)arg;
	t_philo *philo;
	
	philo = (t_philo*)arg;
	if (hold_your_horses(philo) != ALL_OK)
		return (0);
	print_change_of_state(philo, IS_THINKING);
	odd_even_departure(philo);
	pthread_mutex_lock(&philo->room->m_philo_died);
	while(!philo->room->philo_died)
	{
		pthread_mutex_unlock(&philo->room->m_philo_died);
		take_forks(philo);
		print_change_of_state(philo, TAKING_FORKS);
		print_change_of_state(philo, IS_EATING);
		usleep(philo->t_eat * 1000);
		put_down_forks(philo);
		print_change_of_state(philo, IS_SLEEPING);
		usleep(philo->t_sleep * 1000);
		print_change_of_state(philo, IS_THINKING);
		pthread_mutex_lock(&philo->room->m_philo_died);
	}
	return (0);
}

int	run_philo(t_room *room, t_philo *philo)
{
	(void)room;
	t_philo	*current;

	current = philo;
	while (current)
	{
		pthread_create(&current->thread_id, NULL, &philo_routine, current);
		usleep(100);
		current = current->next;
	}
	pthread(&philo->room->monitor_id, NULL, &monitor_routine, philo);
	room->t_sim_start = get_time_in_milliseconds();
	pthread_mutex_lock(&room->m_printing);
	room->time_to_start = true;
	pthread_mutex_unlock(&room->m_printing);
	return (ALL_OK);
}
