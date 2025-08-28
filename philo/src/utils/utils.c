/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:16:52 by maballet          #+#    #+#             */
/*   Updated: 2025/08/28 18:39:21 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

size_t	get_time_in_milliseconds(void)
{
	struct timeval	time;
	if (gettimeofday(&time, NULL))
		return (ERR_GETTIMEOFDAY);
	return (time.tv_sec * 1000000 + time.tv_usec / 1000);
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
	timestamp = get_time_in_milliseconds() - philo->room->t_sim_start;
	if (msg == TAKE_A_FORK && philo->room->philo_died != true)
	{
		printf("%zu %zu has taken a fork\n", timestamp, philo->id);
		printf("%zu %zu has taken a fork\n", timestamp, philo->id);
	}
	if (msg == IS_EATING && philo->room->philo_died != true)
		printf("%zu %zu is eating\n", timestamp, philo->id);
	if (msg == IS_SLEEPING && philo->room->philo_died != true)
		printf("%zu %zu is sleeping\n", timestamp, philo->id);
	if (msg == IS_THINKING && philo->room->philo_died != true)
		printf("%zu %zu is thinking\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->room->m_printing);
	pthread_mutex_unlock(&philo->room->m_philo_died);
}
