/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:57:17 by maballet          #+#    #+#             */
/*   Updated: 2025/08/06 14:17:01 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int argc_error_check(int argc)
{
	if (argc > 6)
		return (print_and_return(TOO_MUCH_ARGC, ERR_PROMPT));
	if (argc < 5)
		return (print_and_return(TOO_FEW_ARGC, ERR_PROMPT));
	return (ALL_OK);
}

int	main(int argc, char **argv)
{
	t_fork	*fork;
	t_room	room;
	t_philo	*philo;
	
	if (argc > 6 || argc < 5)
		return (argc_error_check(argc));
	room_init(argc, argv, &room);
	philo_and_fork_init(&room);
	return (0);
}
