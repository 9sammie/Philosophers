/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:16:52 by maballet          #+#    #+#             */
/*   Updated: 2025/08/07 16:47:50 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

time_t	get_time_in_milliseconds(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec / 1000);
}

int	print_return_int(char *print, int i)
{
	printf("%s", print);
	return(i);
}

t_fork	*print_return_t_fork(char *print, t_fork *error)
{
	printf("%s", print);
	return(error);
}

t_philo	*print_return_t_philo(char *print, t_philo *error)
{
	printf("%s", print);
	return(error);
}
