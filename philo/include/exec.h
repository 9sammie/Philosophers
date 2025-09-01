/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:33:22 by maballet          #+#    #+#             */
/*   Updated: 2025/09/01 14:36:22 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "philo.h"

/*routines_utils.c*/
void	check_philo_down(t_philo *current);
int		check_philo_full(t_philo *c, t_philo *p, size_t f_nbr, size_t p_nbr);
int		comp_forks_id(t_philo *philo);
void	take_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);
/*routines.c*/
void	*monitor_routine(void *arg);
void	*philo_routine(void *arg);
/*run_philo.c*/
int		create_philo_and_monitor(t_room *room, t_philo *philo);
int		manage_all_philo(t_room *room, t_philo *philo);
void	join_thread_when_finished(t_philo *philo);

#endif