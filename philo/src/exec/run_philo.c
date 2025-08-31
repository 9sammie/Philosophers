/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:19:38 by maballet          #+#    #+#             */
/*   Updated: 2025/08/31 18:11:19 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*monitor_routine(void *arg)
{
	(void)arg;
	size_t	philo_nbr;
	size_t	philo_full_nbr;
	t_philo	*philo;
	t_philo	*current;

	philo = (t_philo*)arg;
	philo_nbr = philo->room->philo_nbr;
	usleep(philo->t_die * 1000);
	pthread_mutex_lock(&philo->room->m_philo_died);
	while (philo->room->philo_died == false)
	{
		pthread_mutex_unlock(&philo->room->m_philo_died);
		current = philo;
		philo_full_nbr = 0;
		while (current->next)
		{
			pthread_mutex_lock(&current->m_last_t_eaten);
			if ((get_time_in_ms() - current->last_t_eaten) > current->t_die)
			{
				printf("last_time_eaten: %zu\n", (get_time_in_ms() - current->last_t_eaten));
				printf("%zu, %zu\n", get_time_in_ms(), current->last_t_eaten);
				print_change_of_state(current, MAN_DOWN);
				pthread_mutex_lock(&current->room->m_philo_died);
				current->room->philo_died = true;
				pthread_mutex_unlock(&current->room->m_philo_died);
			}
			pthread_mutex_unlock(&current->m_last_t_eaten);
			pthread_mutex_lock(&current->m_meals_remaining);
			if (current->meals_remaining == 0)
				philo_full_nbr++;
			pthread_mutex_unlock(&current->m_meals_remaining);
			usleep(10);
			current = current->next;
		}
		if (philo_full_nbr == philo_nbr)
		{
			pthread_mutex_lock(&current->room->m_philo_died);
			current->room->philo_died = true;
			pthread_mutex_unlock(&current->room->m_philo_died);
		}
		pthread_mutex_lock(&current->room->m_philo_died);
	}
	pthread_mutex_unlock(&philo->room->m_philo_died);
	return (0);
}

int	hold_your_horses(t_philo *philo)
{
	pthread_mutex_lock(&philo->room->m_printing);
	while (!philo->room->time_to_start)
	{
		pthread_mutex_unlock(&philo->room->m_printing);
		usleep(10);
		pthread_mutex_lock(&philo->room->m_printing);
	}
	pthread_mutex_unlock(&philo->room->m_printing);
	pthread_mutex_lock(&philo->m_last_t_eaten);
	philo->last_t_eaten = get_time_in_ms();
	if (philo->last_t_eaten == ERR_GETTIMEOFDAY)
		return (ERR_GETTIMEOFDAY);
	pthread_mutex_unlock(&philo->m_last_t_eaten);
	return (ALL_OK);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->main_fork->m_available);
	while (!philo->main_fork->available)
	{
		pthread_mutex_unlock(&philo->main_fork->m_available);
        usleep(10);
		pthread_mutex_lock(&philo->main_fork->m_available);
	}
	philo->main_fork->available = false;
	pthread_mutex_unlock(&philo->main_fork->m_available);
	pthread_mutex_lock(&philo->side_fork->m_available);
	while (!philo->side_fork->available)
	{
        pthread_mutex_unlock(&philo->side_fork->m_available);
		usleep(10);
		pthread_mutex_lock(&philo->side_fork->m_available);
	}
	philo->side_fork->available = false;
	pthread_mutex_unlock(&philo->side_fork->m_available);
}

static void	put_down_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_last_t_eaten);
	philo->last_t_eaten = get_time_in_ms();
	pthread_mutex_unlock(&philo->m_last_t_eaten);
	pthread_mutex_lock(&philo->main_fork->m_available);
	philo->main_fork->available = true;
	pthread_mutex_unlock(&philo->main_fork->m_available);
	pthread_mutex_lock(&philo->side_fork->m_available);
	philo->side_fork->available = true;
	pthread_mutex_unlock(&philo->side_fork->m_available);
	pthread_mutex_lock(&philo->m_meals_remaining);
	if (philo->meals_remaining != 0)
		philo->meals_remaining--;
	pthread_mutex_unlock(&philo->m_meals_remaining);
}

void	odd_even_departure(t_philo *philo)
{
	if (!philo->philo_nbr_is_odd)
	{
		if (philo->parity == 0)
			usleep(philo->t_eat * 500);
	}
	else
	{
		if (philo->id % 3 > 0)
			usleep((philo->id % 3) * (philo->t_eat * 333));
	}
	pthread_mutex_lock(&philo->m_last_t_eaten);
	philo->last_t_eaten = get_time_in_ms();
	pthread_mutex_unlock(&philo->m_last_t_eaten);
	pthread_mutex_lock(&philo->room->m_printing);
	if (philo->room->t_sim_start == 0)
		philo->room->t_sim_start = get_time_in_ms();
	pthread_mutex_unlock(&philo->room->m_printing);
}

static void	*philo_routine(void *arg)
{
	(void)arg;
	t_philo *philo;
	
	philo = (t_philo*)arg;
	if (hold_your_horses(philo) != ALL_OK)
		return (0);
	odd_even_departure(philo);
	print_change_of_state(philo, IS_THINKING);
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
	pthread_mutex_unlock(&philo->room->m_philo_died);
	return (0);
}

void	join_threads_on_error(t_philo *philo, size_t thread_count)
{
	t_philo *current;

	current = philo;
	pthread_mutex_lock(&philo->room->m_printing);
	philo->room->time_to_start = true;
	philo->room->philo_died = true;
	pthread_mutex_unlock(&philo->room->m_printing);
	while (current && thread_count >= 0)
	{
		pthread_join(current->thread_id, NULL);
        current = current->next;
		thread_count--;
	}
}

void	join_thread_when_finished(t_philo *philo)
{
	t_philo *current;

	current = philo;
	pthread_join(philo->room->monitor_id, NULL);
	while (current)
	{
		pthread_join(current->thread_id, NULL);
        current = current->next;
	}
}

int	create_philo_and_monitor(t_room *room, t_philo *philo)
{
	(void)room;
	size_t	thread_count;
	t_philo	*current;

	thread_count = 0;
	current = philo;
	while (current)
	{
		if (pthread_create(&current->thread_id, NULL, &philo_routine, current) != ALL_OK)
		{
			join_threads_on_error(philo, thread_count);
			return (ERR_THREAD);
		}
		thread_count++;
		current = current->next;
	}
	pthread_mutex_lock(&room->m_printing);
	room->time_to_start = true;
	pthread_mutex_unlock(&room->m_printing);
	pthread_create(&philo->room->monitor_id, NULL, &monitor_routine, philo);
	return (ALL_OK);
}

int	manage_all_philo(t_room *room, t_philo *philo)
{
	if (create_philo_and_monitor(room, philo) != ALL_OK)
		return(ERR_THREAD);
	pthread_mutex_lock(&room->m_philo_died);
	while (room->philo_died == false)
	{
		pthread_mutex_unlock(&room->m_philo_died);
		usleep(10);
		pthread_mutex_lock(&room->m_philo_died);
	}
	pthread_mutex_unlock(&room->m_philo_died);
	join_thread_when_finished(philo);
	return(ALL_OK);
}
