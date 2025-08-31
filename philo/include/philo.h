/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:11:55 by maballet          #+#    #+#             */
/*   Updated: 2025/08/31 14:41:29 by maballet         ###   ########lyon.fr   */
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

//////////////////   ♠ messages ♠   //////////////////

# define TOO_MUCH_ARGC	"Error: indecent number arguments\n"
# define TOO_FEW_ARGC	"Error: a few more argument would be appreciated\n"
# define PHILO_MAX		"Error: too many philosophers\n"
# define NOT_DIGIT		"Error: Please enter digit parameters only\n"
# define MALLOC_FAIL	"Error: a malloc just failed\n"
# define MUTEX_FAIL		"Error: a mutex just failed\n"
# define NOT_POSITIVE	"Error: negative numbers are ruining the mood...\n"
# define OVERFLOW		"Error: an overflow shall not be accepted\n"
# define EMPTY_PARAM	"Error: empty parameter detected\n"

//////////////////     ♣ enum ♣     //////////////////

typedef enum e__error
{
	ALL_OK,
	ERR_PROMPT,
	ERR,
	ERR_MUTEX,
	ERR_THREAD,
	ERR_GETTIMEOFDAY,
}	t__error;

typedef enum e_change
{
	IS_THINKING,
	TAKING_FORKS,
	IS_EATING,
	IS_SLEEPING,
	MAN_DOWN,
}	t_change;

//////////////////  ♦ structures ♦  //////////////////


typedef struct	s_room
{
	size_t			t_sim_start;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			time_passed;
	int				philo_nbr;
	int				meals_nbr;
	int				errcode;
	bool			philo_died;
	bool			printing;
	bool			meals_left;
	bool			time_to_start;
	pthread_t		monitor_id;
	pthread_mutex_t m_philo_died;
	pthread_mutex_t m_printing;
	pthread_mutex_t m_meals_left;
}	t_room;

typedef struct	s_fork
{
	struct s_fork	*next;
	size_t			id;
	bool			available;
	bool			bool_mutex;
	t_room			*room;
	pthread_mutex_t m_available;
}	t_fork;

typedef struct	s_philo
{
	struct s_philo	*next;
	size_t			id;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			t_die;
	size_t			last_t_eaten;
	int				meals_remaining;
	bool			parity;
	bool			philo_nbr_is_odd;
	t_room			*room;
	t_fork			*main_fork;
	t_fork			*side_fork;
	pthread_mutex_t	m_last_t_eaten;
	pthread_mutex_t	m_meals_remaining;
	pthread_t		thread_id;
}   t_philo;

///////////////////  ♥ fonctions ♥  //////////////////



///// Execution /////

/*exec.c*/
int				create_philo_and_monitor(t_room *room, t_philo *philo);
int				manage_all_philo(t_room *room, t_philo *philo);
void			join_thread_when_finished(t_philo *philo);

///// Parsing /////

/*checks.c*/
int				digit_check(int argc, char **argv);
int				negative_check(int argc, char **argv);
int				overflow_and_empty_check(char **argv);
/*converter.c*/
time_t			ft_atot(const char *nptr);
int				ft_atoi(const char *nptr);
unsigned int	ft_atouint_overflow(const char *nbr);
unsigned int	ft_atouint(const char *nbr);
/*init.c*/
int				room_init(int argc, char **argv, t_room *room);
int				philo_and_fork_init(t_room *room, t_fork **fork, t_philo **philo);
/*lk_ls_fork.c*/
t_fork			*fork_lstnew(int i, t_room *room);
void			fork_lstadd_back(t_fork **lst, t_fork *new);
/*lk_ls_philo.c*/
t_philo			*philo_lstnew(int i, t_room *room, t_fork *fork);
void			philo_lstadd_back(t_philo **lst, t_philo *new);
/*param_check.c*/
int				param_check(int argc, char **argv);

///// Utils /////

/*clean_project.c*/
int				clean_project(t_room *room, t_fork *fork, t_philo *philo);
/*print_return.c*/
int				p_ret_int(char *print, int i, t_room *room, int errcode);
void			p_ret_void(char *print, t_room *room, int errcode);
t_fork			*p_ret_t_fork(char *print, t_fork *err, t_room *room, int errcode);
t_philo			*p_ret_t_philo(char *print, t_philo *err, t_room *room, int errcode);
/*utils.c*/
size_t			get_time_in_ms(void);
void			free_ls_fork(t_fork *fork);
void			free_ls_philo(t_philo *philo);
void			print_change_of_state(t_philo *philo, size_t msg);

#endif