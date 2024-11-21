#include "philosophers.h"

void	ft_err(char *err_msg)
{
	int	i;
	
	i = -1;
	while (err_msg[++i])
		write(1, &err_msg[i], 1);
	exit(1);
}

void	clean(t_table *t)
{
	t_philo *p;
	int	i;

	p = t->philo;
	i = -1;
	while (++i < t->data->nmr_philo)
	{
		p = t->philo + i;
		safe_mutex_handle(&p->p_mtx, DESTROY);
	}
	safe_mutex_handle(&t->table_mtx, DESTROY);
	safe_mutex_handle(&t->print_mtx, DESTROY);
	free (t->forks);
	free (t->philo);
	free (t->data);
}