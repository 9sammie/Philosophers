/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:16:52 by maballet          #+#    #+#             */
/*   Updated: 2025/08/27 13:35:19 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

size_t	get_time_in_milliseconds(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
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
