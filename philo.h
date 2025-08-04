/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:11:55 by maballet          #+#    #+#             */
/*   Updated: 2025/08/04 17:25:22 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define philo_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

//////////////////  ♣    enum    ♣  //////////////////



//////////////////  ♦ structures ♦  //////////////////

typedef struct	s_room
{
	int		philo_nbr;
	int		*all_forks;
	t_philo	*philo;
}	t_room;

typedef struct	s_philo
{
    int eats;
    int thinks;
    int sleeps;
    int  fork_array[2];
	t_room	*room;
	t_fork	*fork;
}   t_philo;

typedef struct	s_fork
{
	pthread_mutex_t lock;
	int	available;
}	t_fork;

#endif