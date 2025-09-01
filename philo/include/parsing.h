/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:52:17 by maballet          #+#    #+#             */
/*   Updated: 2025/09/01 14:36:26 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "philo.h"
# include <limits.h>

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
int				philo_fork_init(t_room *room, t_fork **fork, t_philo **philo);
/*lk_ls_fork.c*/
t_fork			*fork_lstnew(int i, t_room *room);
void			fork_lstadd_back(t_fork **lst, t_fork *new);
/*lk_ls_philo.c*/
t_philo			*philo_lstnew(int i, t_room *room, t_fork *fork);
void			philo_lstadd_back(t_philo **lst, t_philo *new);
/*param_check.c*/
int				param_check(int argc, char **argv);

#endif