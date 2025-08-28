/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:19:38 by maballet          #+#    #+#             */
/*   Updated: 2025/08/28 15:06:00 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	hold_your_horses(t_philo *philo)
{
	pthread_mutex_lock(&philo->room->m_printing);
	while (!philo->room->time_to_start)
	{
		pthread_mutex_unlock(&philo->room->m_printing);
		usleep(1);
		pthread_mutex_lock(&philo->room->m_printing);
	}
	pthread_mutex_unlock(&philo->room->m_printing);
	pthread_mutex_lock(&philo->m_last_t_eaten);
	philo->last_t_eaten = get_time_in_milliseconds();
	if (philo->last_t_eaten == ERR_GETTIMEOFDAY)
		return (ERR_GETTIMEOFDAY);
	pthread_mutex_unlock(&philo->m_last_t_eaten);
	if (philo->parity == 1)
		usleep(philo->t_eat/2);
	return (ALL_OK);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->main_fork->m_available);
	philo->main_fork->available = false;
	pthread_mutex_unlock(&philo->main_fork->m_available);
	pthread_mutex_lock(&philo->side_fork->m_available);
	philo->side_fork->available = false;
	print_change_of_state(philo, TAKE_A_FORK);
	print_change_of_state(philo, TAKE_A_FORK);
	pthread_mutex_unlock(&philo->side_fork->m_available);
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

static void	*philo_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo*)arg;
	printf("hey\n");
	if (hold_your_horses(philo) != ALL_OK)
		return (0);
	print_change_of_state(philo, IS_THINKING);
	pthread_mutex_lock(&philo->room->m_philo_died);
	while(!philo->room->philo_died)
	{
		pthread_mutex_unlock(&philo->room->m_philo_died);
		take_forks(philo);
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

int	exec_philo(t_room *room, t_philo *philo)
{
	(void)room;
	t_philo	*current;

	current = philo;
	while (current)
	{
		// printf("hey\n");
		pthread_create(&current->thread_id, NULL, &philo_routine, current);
		current = current->next;
	}
	printf("hey\n");
	room ->t_sim_start = get_time_in_milliseconds();
	room->time_to_start = true;
	return (ALL_OK);
}
