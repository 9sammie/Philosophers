/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:57:17 by maballet          #+#    #+#             */
/*   Updated: 2025/08/28 17:52:19 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

// static void debug_print(t_room *room, t_philo *philo)
// {
// 	t_philo *current;
// 	int	i;
	
// 	printf("---  ROOM  ---\n\n\n");
// 	printf("philo_nbr: %d\n", room->philo_nbr);
// 	printf("t_die: %ld\n", room->t_die);
// 	printf("t_eat: %ld\n", room->t_eat);
// 	printf("t_sleep: %ld\n", room->t_sleep);
// 	printf("meals_nbr: %d\n\n", room->meals_nbr);
// 	current = philo;
// 	i = 1;
// 	printf("---  PHILOS  ---\n\n\n");
// 	while(current)
// 	{
// 		printf("- philo nbr %d -\n", i);
// 		printf("id: %zu\n", current->id);
// 		printf("parity: %d\n", current->parity);
// 		printf("last time no eat: %ld\n", current->last_t_eaten);
// 		printf("main fork id: %zu\n", current->main_fork->id);
// 		printf("side fork id: %zu\n\n", current->side_fork->id);
// 		current = current->next;
// 		i++;
// 	}
// }

int	main(int argc, char **argv)
{
	t_fork	*fork;
	t_room	room;
	t_philo	*philo;
	
	fork = NULL;
	philo = NULL;
	if (param_check(argc, argv) != ALL_OK)
		return (ERR_PROMPT);
	if (room_init(argc, argv, &room) != ALL_OK)
		return(clean_project(&room, fork, philo));
	if (philo_and_fork_init(&room, &fork, &philo) != ALL_OK)
		return(clean_project(&room, fork, philo));
	exec_philo(&room, philo);
	// debug_print(&room, philo);
	pthread_mutex_lock(&room.m_philo_died);
	while (room.philo_died == false)
	{
		pthread_mutex_unlock(&room.m_philo_died);
		usleep(100);
		pthread_mutex_lock(&room.m_philo_died);
	}
	return (clean_project(&room, fork, philo));
}
