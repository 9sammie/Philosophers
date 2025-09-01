/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:57:17 by maballet          #+#    #+#             */
/*   Updated: 2025/09/01 14:17:29 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "exec.h"
#include "parsing.h"

int	main(int argc, char **argv)
{
	t_room	room;
	t_fork	*fork;
	t_philo	*philo;

	fork = NULL;
	philo = NULL;
	if (param_check(argc, argv) != ALL_OK)
		return (ERR_PROMPT);
	if (room_init(argc, argv, &room) != ALL_OK)
		return (clean_project(&room, fork, philo));
	if (philo_fork_init(&room, &fork, &philo) != ALL_OK)
		return (clean_project(&room, fork, philo));
	if (manage_all_philo(&room, philo) != ALL_OK)
		return (clean_project(&room, fork, philo));
	return (clean_project(&room, fork, philo));
}
