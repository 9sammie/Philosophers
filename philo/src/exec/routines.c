/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:10:04 by maballet          #+#    #+#             */
/*   Updated: 2025/09/01 14:14:18 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	hold_your_horses(t_philo *philo)
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

static void	odd_even_departure(t_philo *philo)
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

static void	parse_all_philo(t_philo *current, size_t philo_full_nbr)
{
	while (current->next)
	{
		check_philo_down(current);
		pthread_mutex_lock(&current->m_meals_remaining);
		if (current->meals_remaining == 0)
			philo_full_nbr++;
		pthread_mutex_unlock(&current->m_meals_remaining);
		usleep(10);
		current = current->next;
	}
}

void	*monitor_routine(void *arg)
{
	size_t	philo_nbr;
	size_t	philo_full_nbr;
	t_philo	*philo;
	t_philo	*current;

	(void)arg;
	philo = (t_philo *)arg;
	philo_nbr = philo->room->philo_nbr;
	usleep(philo->t_die * 1000);
	pthread_mutex_lock(&philo->room->m_philo_died);
	while (philo->room->philo_died == false)
	{
		pthread_mutex_unlock(&philo->room->m_philo_died);
		current = philo;
		philo_full_nbr = 1;
		parse_all_philo(current, philo_full_nbr);
		if (check_philo_full(current, philo, philo_full_nbr, philo_nbr))
			break ;
		pthread_mutex_lock(&current->room->m_philo_died);
	}
	pthread_mutex_unlock(&philo->room->m_philo_died);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	(void)arg;
	philo = (t_philo *)arg;
	if (hold_your_horses(philo) != ALL_OK)
		return (0);
	odd_even_departure(philo);
	print_change_of_state(philo, IS_THINKING);
	pthread_mutex_lock(&philo->room->m_philo_died);
	while (!philo->room->philo_died)
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
