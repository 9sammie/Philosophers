/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:15:39 by maballet          #+#    #+#             */
/*   Updated: 2025/08/31 20:30:12 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	room_init(int argc, char **argv, t_room *room)
{
	room->errcode = 10;
	room->t_sim_start = 0;
	room->philo_nbr = ft_atoi(argv[1]); 
	room->t_die = ft_atouint(argv[2]);
	room->t_eat = ft_atouint(argv[3]);
	room->t_sleep = ft_atouint(argv[4]);
	if (argc == 6)
		room->meals_nbr = ft_atoi(argv[5]);
	else
		room->meals_nbr = -1;
	room->philo_died = false;
	room->printing = true;
	room->time_to_start = false;
	if(pthread_mutex_init(&room->m_philo_died, NULL) != 0)
		return(p_ret_int(MUTEX_FAIL, ERR_MUTEX, room, -1));
	if(pthread_mutex_init(&room->m_meals_left, NULL) != 0)
		return(p_ret_int(MUTEX_FAIL, ERR_MUTEX, room, 1));
	if(pthread_mutex_init(&room->m_printing, NULL) != 0)
		return(p_ret_int(MUTEX_FAIL, ERR_MUTEX, room, 2));
	return (0);
}

int	fork_init(t_fork **fork, t_fork *new_fork, t_room *room)
{
	int	i;

	i = 1;
	new_fork = fork_lstnew(i, room);
	if (new_fork == NULL)
		return(ERR_MALLOC);
	fork_lstadd_back(fork, new_fork);
	i++;
	while (i <= room->philo_nbr)
	{
		new_fork = fork_lstnew(i, room);
		if (new_fork == NULL)
			return(ERR_MALLOC);
		fork_lstadd_back(fork, new_fork);
		i++;
	}
	return (ALL_OK);
}

int	philo_init(t_philo **philo, t_philo *new_philo, t_room *room, t_fork **fork)
{
	int i;

	i = 1;
	new_philo = philo_lstnew(i, room, *fork);
	if (new_philo == NULL)
		return(ERR_MALLOC);
	philo_lstadd_back(philo, new_philo);
	i++;
	while (i <= room->philo_nbr)
	{
		new_philo = philo_lstnew(i, room, *fork);
		if (new_philo == NULL)
			return(ERR_MALLOC);
		philo_lstadd_back(philo, new_philo);
		i++;
	}
	return (ALL_OK);
}

int	philo_and_fork_init(t_room *room, t_fork **fork, t_philo **philo)
{
	t_fork *new_fork;
	t_philo *new_philo;
	
	new_fork = NULL;
	new_philo = NULL;
	if (fork_init(fork, new_fork, room) != ALL_OK)
		return (ERR_MALLOC);
	if (philo_init(philo, new_philo, room, fork) != ALL_OK)
		return (ERR_MALLOC);
	return(ALL_OK);
}
