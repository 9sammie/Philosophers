/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:11:55 by maballet          #+#    #+#             */
/*   Updated: 2025/08/06 17:57:17 by maballet         ###   ########lyon.fr   */
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
# define OMG "Dear lord a malloc just failed "

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

t_fork	*fork_lstnew(int i);
void	fork_lstadd_back(t_fork **lst, t_fork *new);
t_philo	*philo_lstnew(int i, int nbr_philo, t_fork *fork);
void	philo_lstadd_back(t_philo **lst, t_philo *new);
int		ft_atoi(const char *nptr);
time_t	ft_atot(const char *nptr);
void	room_init(int argc, char **argv, t_room *room);
void	philo_and_fork_init(t_room *room);
int	print_and_return(char *print, int i);
time_t	get_time_in_milliseconds(void);

#endif