/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lk_ls_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:05:32 by maballet          #+#    #+#             */
/*   Updated: 2025/08/26 18:53:04 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

t_fork	*fork_lstnew(int i, t_room *room)
{
	t_fork	*new;
	
	new = malloc(sizeof (t_fork));
	if (!new)
		return (p_ret_t_fork(MALLOC_FAIL, NULL, room, 3));
	new->next = NULL;
	new->available = true;
	if (pthread_mutex_init(&new->mutex, NULL) != 0)
	{
		free(new);
		return (p_ret_t_fork(MUTEX_FAIL, NULL, room, 3));
	}
	new->id = i;
	new->room = room;
	return (new);
}

static t_fork	*fork_lstlast(t_fork *lst)
{
	t_fork	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

void	fork_lstadd_back(t_fork **lst, t_fork *new)
{
	t_fork	*current;

	if (!lst)
		return ;
	current = fork_lstlast(*lst);
	if (current)
		current->next = new;
	else
		*lst = new;
}
