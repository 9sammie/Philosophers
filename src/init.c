/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:15:39 by maballet          #+#    #+#             */
/*   Updated: 2025/08/06 16:01:40 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	room_init(int argc, char **argv, t_room *room)
{
	room->start_time = 0;
	room->philo_nbr = ft_atoi(argv[1]); 
	room->die_time = ft_atot(argv[2]);
	room->eat_time = ft_atot(argv[3]);
	room->sleep_time = ft_atot(argv[4]);
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
