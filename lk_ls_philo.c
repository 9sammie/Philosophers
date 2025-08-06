# include "philo.h"

t_fork	*find_fork_pointer(char *s, int i, t_fork *fork, int nbr_philo)
{
	t_fork *current;
	int		j;

	current = fork;
	if (s == "right" && i == nbr_philo)
		return (current);
	j = 1;
	while (j != i)
	{
		current = current->next;
		j++;
	}
	if (s == "right")
		current = current->next;
	return (current);
}

t_philo	*philo_lstnew(int i, int nbr_philo, t_fork *fork)
{
	t_philo	*new;

	new = malloc(sizeof (t_philo));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->id = i;
	new->still_alive = true;
	new->left_fork = find_fork_pointer("left", i, fork, nbr_philo);
	new->right_fork = find_fork_pointer("right", i, fork, nbr_philo);
	return (new);
}

t_philo	*philo_lstlast(t_philo *lst)
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
