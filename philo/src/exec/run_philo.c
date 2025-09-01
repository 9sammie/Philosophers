/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:19:38 by maballet          #+#    #+#             */
/*   Updated: 2025/09/01 14:11:31 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	join_threads_on_error(t_philo *philo, size_t thread_count)
{
	t_philo	*current;

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
	t_philo	*current;

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
	size_t	thread_count;
	t_philo	*curr;

	(void)room;
	thread_count = 0;
	curr = philo;
	while (curr)
	{
		if (pthread_create(&curr->thread_id, NULL, &philo_routine, curr) != 0)
		{
			join_threads_on_error(philo, thread_count);
			return (ERR_THREAD);
		}
		thread_count++;
		curr = curr->next;
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
		return (ERR_THREAD);
	pthread_mutex_lock(&room->m_philo_died);
	while (room->philo_died == false)
	{
		pthread_mutex_unlock(&room->m_philo_died);
		usleep(10);
		pthread_mutex_lock(&room->m_philo_died);
	}
	pthread_mutex_unlock(&room->m_philo_died);
	join_thread_when_finished(philo);
	return (ALL_OK);
}
