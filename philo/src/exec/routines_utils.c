/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:16:39 by maballet          #+#    #+#             */
/*   Updated: 2025/09/01 14:16:05 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philo_down(t_philo *current)
{
	pthread_mutex_lock(&current->m_last_t_eaten);
	if ((get_time_in_ms() - current->last_t_eaten) > current->t_die)
	{
		print_change_of_state(current, MAN_DOWN);
		pthread_mutex_lock(&current->room->m_philo_died);
		current->room->philo_died = true;
		pthread_mutex_unlock(&current->room->m_philo_died);
	}
	pthread_mutex_unlock(&current->m_last_t_eaten);
}

int	check_philo_full(t_philo *c, t_philo *p, size_t f_nbr, size_t p_nbr)
{
	if (f_nbr == p_nbr)
	{
		print_change_of_state(p, PHILO_FULL);
		pthread_mutex_lock(&c->room->m_philo_died);
		c->room->philo_died = true;
		pthread_mutex_unlock(&c->room->m_philo_died);
		return (1);
	}
	return (0);
}

int	comp_forks_id(t_philo *philo)
{
	if (philo->main_fork->id == philo->side_fork->id)
	{
		print_change_of_state(philo, TAKING_1_FORK);
		pthread_mutex_lock(&philo->room->m_philo_died);
		philo->room->philo_died = true;
		pthread_mutex_unlock(&philo->room->m_philo_died);
		usleep(philo->t_die * 1000);
		return (ERR);
	}
	return (ALL_OK);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->main_fork->m_available);
	while (!philo->main_fork->available)
	{
		pthread_mutex_unlock(&philo->main_fork->m_available);
		usleep(500);
		pthread_mutex_lock(&philo->main_fork->m_available);
	}
	philo->main_fork->available = false;
	pthread_mutex_unlock(&philo->main_fork->m_available);
	if (comp_forks_id(philo) != ALL_OK)
		return ;
	pthread_mutex_lock(&philo->side_fork->m_available);
	while (!philo->side_fork->available)
	{
		pthread_mutex_unlock(&philo->side_fork->m_available);
		usleep(500);
		pthread_mutex_lock(&philo->side_fork->m_available);
	}
	philo->side_fork->available = false;
	pthread_mutex_unlock(&philo->side_fork->m_available);
}

void	put_down_forks(t_philo *philo)
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
