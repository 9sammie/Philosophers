/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:57:17 by maballet          #+#    #+#             */
/*   Updated: 2025/08/07 16:53:24 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	main(int argc, char **argv)
{
	t_fork	*fork;
	t_room	room;
	t_philo	*philo;
	
	fork = NULL;
	philo = NULL;
	if (arg_check(argc, argv) != ALL_OK)
		return (ERR_PROMPT);
	room_init(argc, argv, &room);
	philo_and_fork_init(&room, fork, philo);
	return (0);
}
