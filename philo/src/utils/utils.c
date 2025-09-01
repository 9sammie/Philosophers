/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:16:52 by maballet          #+#    #+#             */
/*   Updated: 2025/09/01 16:41:12 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

size_t	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (ERR_GETTIMEOFDAY);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

void	free_ls_fork(t_fork *fork)
{
	t_fork	*next;

	while (fork)
	{
		next = fork->next;
		free(fork);
		fork = next;
	}
}

void	free_ls_philo(t_philo *philo)
{
	t_philo	*next;

	while (philo)
	{
		next = philo->next;
		free(philo);
		philo = next;
	}
}

void	print_change_of_state(t_philo *philo, size_t msg)
{
	size_t	timestamp;

	pthread_mutex_lock(&philo->room->m_printing);
	pthread_mutex_lock(&philo->room->m_philo_died);
	timestamp = get_time_in_ms() - philo->room->t_sim_start;
	if (msg == MAN_DOWN && philo->room->philo_died != true)
		printf("%zu %zu died\n", timestamp, philo->id);
	if (msg == PHILO_FULL && philo->room->philo_died != true)
		printf("%zu All ate %d meals\n", timestamp, philo->room->meals_nbr);
	if (msg == IS_THINKING && philo->room->philo_died != true)
		printf("%zu %zu is thinking\n", timestamp, philo->id);
	if (msg == TAKING_FORKS && philo->room->philo_died != true)
	{
		printf("%zu %zu has taken a fork\n", timestamp, philo->id);
		printf("%zu %zu has taken a fork\n", timestamp, philo->id);
	}
	if (msg == TAKING_1_FORK && philo->room->philo_died != true)
		printf("%zu %zu has taken a fork\n", timestamp, philo->id);
	if (msg == IS_EATING && philo->room->philo_died != true)
		printf("%zu %zu is eating\n", timestamp, philo->id);
	if (msg == IS_SLEEPING && philo->room->philo_died != true)
		printf("%zu %zu is sleeping\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->room->m_printing);
	pthread_mutex_unlock(&philo->room->m_philo_died);
}
