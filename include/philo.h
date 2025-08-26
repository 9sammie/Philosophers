/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:11:55 by maballet          #+#    #+#             */
/*   Updated: 2025/08/26 15:48:42 by maballet         ###   ########lyon.fr   */
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
# include <stdlib.h>

//////////////////  ♠  messages  ♠  //////////////////

# define TOO_MUCH_ARGC	"Error: indecent number arguments\n"
# define TOO_FEW_ARGC	"Error: a few more argument would be appreciated\n"
# define PHILO_MAX		"Error: too many philosophers\n"
# define NOT_DIGIT		"Error: Please enter digit parameters only\n"
# define MALLOC_FAIL	"Error: a malloc just failed\n"
# define MUTEX_FAIL		"Error: a mutex just failed\n"

//////////////////  ♣    enum    ♣  //////////////////

typedef enum e__error
{
	ALL_OK,
	ERR_PROMPT,
	ERR_MUTEX,
}	t__error;

//////////////////  ♦ structures ♦  //////////////////


typedef struct	s_room
{
	time_t			t_start;
	time_t			t_die;
	time_t			t_eat;
	time_t			t_sleep;
	time_t			time_passed;
	int				philo_nbr;
	int				meals_nbr;
	int				errcode;
	bool			philo_died;
	bool			printable;
	bool			meals_left;
	pthread_mutex_t m_philo_died;
	pthread_mutex_t m_printable;
	pthread_mutex_t m_meals_left;
}	t_room;

typedef struct	s_fork
{
	struct s_fork	*next;
	size_t			id;
	bool			available;
	bool			bool_mutex;
	pthread_mutex_t mutex;
	t_room			*room;
}	t_fork;

typedef struct	s_philo
{
	struct s_philo	*next;
	size_t			id;
	int				meals_remaining;
	bool			parity;
	t_room			*room;
	t_fork			*main_fork;
	t_fork			*side_fork;
	time_t			last_t_no_eat;
	pthread_mutex_t	m_last_t_no_eat;
	pthread_mutex_t	m_meals_remaining;
}   t_philo;

///////////////////  ♥ fonctions ♥  //////////////////



///// Execution /////


///// Parsing /////

/*atoi_atot.c*/
time_t	ft_atot(const char *nptr);
int		ft_atoi(const char *nptr);
/*init.c*/
int		room_init(int argc, char **argv, t_room *room);
int		philo_and_fork_init(t_room *room, t_fork **fork, t_philo **philo);
/*lk_ls_fork.c*/
t_fork	*fork_lstnew(int i, t_room *room);
void	fork_lstadd_back(t_fork **lst, t_fork *new);
/*lk_ls_philo.c*/
t_philo	*philo_lstnew(int i, t_room *room, t_fork *fork);
void	philo_lstadd_back(t_philo **lst, t_philo *new);
/*param_check.c*/
int		param_check(int argc, char **argv);

///// Utils /////

/*clean_project.c*/
int	clean_project(t_room *room, t_fork *fork, t_philo *philo);
/*print_return.c*/
int		p_ret_int(char *print, int i, t_room *room, int errcode);
void	p_ret_void(char *print, t_room *room, int errcode);
t_fork	*p_ret_t_fork(char *print, t_fork *err, t_room *room, int errcode);
t_philo	*p_ret_t_philo(char *print, t_philo *err, t_room *room, int errcode);
/*utils.c*/
time_t	get_time_in_milliseconds(void);

#endif