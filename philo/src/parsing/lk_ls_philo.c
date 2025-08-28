/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lk_ls_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 06:39:10 by maballet          #+#    #+#             */
/*   Updated: 2025/08/28 13:53:09 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static t_fork	*find_fork_pointer(bool r_fork, int i, t_fork *f, int nbr_philo)
{
	t_fork *current;
	int		j;

	current = f;
	if (r_fork == true && i == nbr_philo)
		return (current);
	j = 1;
	while (j != i)
	{
		current = current->next;
		j++;
	}
	if (r_fork == true)
		current = current->next;
	return (current);
}

t_philo	*philo_lstnew(int i, t_room *room, t_fork *fork)
{
	t_philo	*new;

	new = malloc(sizeof (t_philo));
	if (!new)
		return (p_ret_t_philo(MALLOC_FAIL, NULL, room, 4));
	new->next = NULL;
	new->id = i;
	new->main_fork = find_fork_pointer(false, i, fork, room->philo_nbr);
	new->side_fork = find_fork_pointer(true, i, fork, room->philo_nbr);
	if (i % 2 == 0)
		new->parity = 0;
	else
		new->parity = 1;
	new->last_t_eaten = 0;
	new->meals_remaining = room->meals_nbr;
	new->room = room;
	new->t_eat = room->t_eat;
	new->t_sleep = room->t_sleep;
		if (pthread_mutex_init(&new->m_last_t_eaten, NULL) != 0)
	{
		free(new);
		return (p_ret_t_philo(MUTEX_FAIL, NULL, room, 4));
	}
		if (pthread_mutex_init(&new->m_meals_remaining, NULL) != 0)
	{
		free(new);
		return (p_ret_t_philo(MUTEX_FAIL, NULL, room, 5));
	}
	return (new);
}

static t_philo	*philo_lstlast(t_philo *lst)
{
	t_philo	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

void	philo_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*current;

	if (!lst)
		return ;
	current = philo_lstlast(*lst);
	if (current)
		current->next = new;
	else
		*lst = new;
}
