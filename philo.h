/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:11:55 by maballet          #+#    #+#             */
/*   Updated: 2025/08/06 10:43:00 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <time.h>

//////////////////  ♠  messages  ♠  //////////////////

# define TOO_MUCH_ARGC "indecent number arguments 🧘🏻‍♂️\n"
# define TOO_FEW_ARGC "A few more argument would be appreciated 🙏🏻🙏🏻🙏🏻\n"

//////////////////  ♣    enum    ♣  //////////////////

typedef enum e__error
{
	ALL_OK = 0,
	ERR_PROMPT = 1,
	ERR_MALLOC = 2,
}	t__error;

//////////////////  ♦ structures ♦  //////////////////

typedef struct	s_fork
{
	struct s_fork	*next;
	size_t			id;
	bool			fork_available;
	pthread_mutex_t m_fork;
}	t_fork;

typedef struct	s_room
{
	time_t			start_time;
	time_t			die_time;
	time_t			eat_time;
	time_t			sleep_time;
	int				philo_nbr;
	int				meals_remaining;
	t_fork			*forks;
	bool			philo_died;
	pthread_mutex_t m_philo_died;
}	t_room;

typedef struct	s_philo
{
	struct s_philo	*next;
	size_t			id;
	t_room			*room;
	t_fork			*left_fork;
	t_fork			*right_fork;
	time_t			still_alive;
}   t_philo;

///////////////////  ♥ fonctions ♥  //////////////////


#endif