/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_project.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:46:12 by maballet          #+#    #+#             */
/*   Updated: 2025/08/31 14:41:59 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static void	destroy_room(t_room *room)
{
	pthread_mutex_destroy(&room->m_philo_died);
	pthread_mutex_destroy(&room->m_meals_left);
	pthread_mutex_destroy(&room->m_meals_left);
}

static void	destroy_fork(t_fork *fork, t_room *room)
{
	t_fork *current;
	int	mutex_init_count;

	destroy_room(room);
	current = fork;
	if (current->next == NULL)
		return;
	mutex_init_count = 0;
	while (current->next)
	{
		current = current->next;
		mutex_init_count++;
	}
	current = fork;
	while (mutex_init_count > 0)
	{
		pthread_mutex_destroy(&current->m_available);
		current = current->next;
		mutex_init_count--;
	}
	free_ls_fork(fork);
}

static void	destroy_philo(t_philo *philo, t_fork *fork, t_room *room)
{
	t_fork	*f_current;
	t_philo	*p_current;
	int		mutex_init_count;

	destroy_room(room);
	f_current = fork;
	while (f_current->next)
	{
		pthread_mutex_destroy(&f_current->m_available);
		f_current = f_current->next;
	}
	free_ls_fork(fork);
	p_current = philo;
	mutex_init_count = 0;
	while (mutex_init_count > 0)
	{
		pthread_mutex_destroy(&p_current->m_last_t_eaten);
		pthread_mutex_destroy(&p_current->m_meals_remaining);
		p_current = p_current->next;
		mutex_init_count--;
	}
	free_ls_philo(philo);
}

static void	destroy_all(t_philo *philo, t_fork *fork, t_room *room)
{
	t_fork	*f_current;
	t_philo	*p_current;

	destroy_room(room);
	f_current = fork;
	while (f_current->next)
	{
		pthread_mutex_destroy(&f_current->m_available);
		f_current = f_current->next;
	}
	free_ls_fork(fork);
	p_current = philo;
	while (p_current->next)
	{
		pthread_mutex_destroy(&p_current->m_last_t_eaten);
		pthread_mutex_destroy(&p_current->m_meals_remaining);
		p_current = p_current->next;
	}
	free_ls_philo(philo);
}

int	clean_project(t_room *room, t_fork *fork, t_philo *philo)
{
	if (room->errcode == 1)
		pthread_mutex_destroy(&room->m_philo_died);
	if (room->errcode == 2)
	{
		pthread_mutex_destroy(&room->m_philo_died);
		pthread_mutex_destroy(&room->m_meals_left);
	}
	if (room->errcode == 3)
		destroy_fork(fork, room);
	if (room->errcode == 4)
		destroy_philo(philo, fork, room);
	if (room->errcode == 10)
		destroy_all(philo, fork, room);
	if (room->errcode != 10)
		return (ERR);
	return (ALL_OK);
}
