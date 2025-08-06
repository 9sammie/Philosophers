/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:57:17 by maballet          #+#    #+#             */
/*   Updated: 2025/08/06 14:08:59 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

time_t	get_time_in_milliseconds(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec / 1000);
}

time_t	ft_atot(const char *nptr)
{
	int		i;
	time_t	sign;
	time_t	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

int	print_and_return(char *print, int i)
{
	printf("%s", print);
	return(i);
}

int argc_error_check(int argc)
{
	if (argc > 6)
		return (print_and_return(TOO_MUCH_ARGC, ERR_PROMPT));
	if (argc < 5)
		return (print_and_return(TOO_FEW_ARGC, ERR_PROMPT));
	return (ALL_OK);
}

void	room_init(int argc, char **argv, t_room *room)
{
	room->start_time = 0;
	room->philo_nbr = ft_atoi(argv[1]); 
	room->die_time = ft_atol(argv[2]);
	room->eat_time = ft_atol(argv[3]);
	room->sleep_time = ft_atol(argv[4]);
	if (argc == 6)
		room->meals_remaining = ft_atoi(argv[5]);
	else
		room->meals_remaining = -1;
	room->philo_died = false;
}

void	philo_and_fork_init(t_room *room)
{
	t_fork	*fork;
	t_philo	*philo;
	int		i;
	
	i = 1;
	while (i <= room->philo_nbr)
	{
		
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_fork	*fork;
	t_room	room;
	t_philo	*philo;
	
	if (argc > 6 || argc < 5)
		return (argc_error_check(argc));
	room_init(argc, argv, &room);
	philo_and_fork_init(&room);
	return (0);
}
