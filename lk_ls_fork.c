/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lk_ls_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:05:32 by maballet          #+#    #+#             */
/*   Updated: 2025/08/06 14:08:29 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

t_fork	*fork_lstnew(int i)
{
	t_fork	*new;
	
	new = malloc(sizeof (t_philo));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->fork_available = true;
	pthread_mutex_init(&new->m_fork, NULL);
	new->id = i;
}

t_fork	*fork_lstlast(t_fork *lst)
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
