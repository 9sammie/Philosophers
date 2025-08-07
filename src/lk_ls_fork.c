/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lk_ls_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:05:32 by maballet          #+#    #+#             */
/*   Updated: 2025/08/07 16:24:55 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

t_fork	*fork_lstnew(int i)
{
	t_fork	*new;
	
	new = malloc(sizeof (t_fork));
	if (!new)
		return (print_return_t_fork(MALLOC_FAIL, NULL));
	new->next = NULL;
	new->fork_available = true;
	if (pthread_mutex_init(&new->m_fork, NULL) != 0)
	{
		free(new);
		return (print_return_t_fork(MUTEX_FAIL, NULL));
	}
	new->id = i;
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
