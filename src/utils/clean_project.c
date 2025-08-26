/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_project.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:46:12 by maballet          #+#    #+#             */
/*   Updated: 2025/08/26 19:08:15 by maballet         ###   ########lyon.fr   */
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
	int	i;

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
	i = 0;
	while (i < mutex_init_count)
	{
		pthread_mutex_destroy(&fork->mutex);
		current = current->next;
	}
}

static void	destroy_philo(t_philo *philo, t_fork *fork, t_room *room)
{
	t_fork	*f_current;
	t_philo	*p_current;
	int		mutex_init_count;
	int		i;

	destroy_room(room);
	while (fork->next)
	{
		pthread_mutex_destroy(&fork->mutex);
		f_current = f_current->next;
	}
	i = 0;
	mutex_init_count = 0;
	while (i < mutex_init_count)
	{
		pthread_mutex_destroy(&philo->m_last_t_no_eat);
		pthread_mutex_destroy(&philo->m_meals_remaining);
		p_current = p_current->next;
	}
	if (room->errcode == 5)
		pthread_mutex_destroy(&philo->m_last_t_no_eat);
}

static void	destroy_all(t_philo *philo, t_fork *fork, t_room *room)
{
	t_fork	*f_current;
	t_philo	*p_current;

	destroy_room(room);
	while (fork->next)
	{
		pthread_mutex_destroy(&fork->mutex);
		f_current = f_current->next;
	}
	while (philo->next)
	{
		pthread_mutex_destroy(&philo->m_last_t_no_eat);
		pthread_mutex_destroy(&philo->m_meals_remaining);
		p_current = p_current->next;
	}
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
		return (ERR_MUTEX);
	else
		return (ALL_OK);
}

