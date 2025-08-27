/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_return.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:35:10 by maballet          #+#    #+#             */
/*   Updated: 2025/08/27 13:20:39 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	p_ret_int(char *print, int i, t_room *room, int errcode)
{
	printf("%s", print);
	if (room)
		room->errcode = errcode;
	if (errcode == 0)
		return(i);
	else
		room->philo_died = true;
	return(i);
}

void	p_ret_void(char *print, t_room *room, int errcode)
{
	printf("%s", print);
	if (room)
		room->errcode = errcode;
	if (errcode == 0)
		return;
	else
		room->philo_died = true;
}

t_fork	*p_ret_t_fork(char *print, t_fork *err, t_room *room, int errcode)
{
	printf("%s", print);
	if (room)
		room->errcode = errcode;
	if (errcode == 0)
		return(err);
	else
		room->philo_died = true;
	return(err);
}

t_philo	*p_ret_t_philo(char *print, t_philo *err, t_room *room, int errcode)
{
	printf("%s", print);
	if (room)
		room->errcode = errcode;
	if (errcode == 0)
		return(err);
	else
		room->philo_died = true;
	return(err);
}