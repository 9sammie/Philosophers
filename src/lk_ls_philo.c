# include "philo.h"

static t_fork	*find_fork_pointer(bool is_right_fork, int i, t_fork *fork, int nbr_philo)
{
	t_fork *current;
	int		j;

	current = fork;
	if (is_right_fork == true && i == nbr_philo)
		return (current);
	j = 1;
	while (j != i)
	{
		current = current->next;
		j++;
	}
	if (is_right_fork == true)
		current = current->next;
	return (current);
}

t_philo	*philo_lstnew(int i, int nbr_philo, t_fork *fork)
{
	t_philo	*new;

	new = malloc(sizeof (t_philo));
	if (!new)
		return (print_return_t_philo(MALLOC_FAIL, NULL));
	new->next = NULL;
	new->id = i;
	new->still_alive = true;
	new->left_fork = find_fork_pointer(false, i, fork, nbr_philo);
	new->right_fork = find_fork_pointer(true, i, fork, nbr_philo);
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
