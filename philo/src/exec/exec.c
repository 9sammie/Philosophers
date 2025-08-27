/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:19:38 by maballet          #+#    #+#             */
/*   Updated: 2025/08/27 20:52:28 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	hold_your_horses(t_philo *philo)
{
	
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->main_fork->m_available);
	pthread_mutex_lock(&philo->side_fork->m_available);
}

void	philo_routine(t_philo *philo)
{
	
	pthread_mutex_lock(&philo->room->m_philo_died);
	while(!philo->room->philo_died)
	{
		pthread_mutex_unlock(&philo->room->m_philo_died);
		print_change_of_state(philo, IS_THINKING);
		take_forks(philo);
		print_change_of_state(philo, IS_EATING);
		usleep(philo->t_eat * 1000);
		pthread_mutex_lock(&philo->main_fork->m_available);
		philo->main_fork->available = true;
		pthread_mutex_unlock(&philo->main_fork->m_available);
		pthread_mutex_lock(&philo->side_fork->m_available);
		philo->side_fork->available = true;
		pthread_mutex_unlock(&philo->side_fork->m_available);
		print_change_of_state(philo, IS_SLEEPING);
		usleep(philo->t_sleep * 1000);
		print_change_of_state(philo, IS_THINKING);
		pthread_mutex_lock(&philo->room->m_philo_died);
	}
}

int	exec_philo(t_room *room, t_philo *philo)
{
	t_philo	*current;
	while (philo)
	{
		pthread_create(&(current->thread_id), NULL, &philo_routine, NULL);
		current = current->next;
	}
}
