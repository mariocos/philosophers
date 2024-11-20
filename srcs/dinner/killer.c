#include "../philosophers.h"

void	ready_to_hunt(void)
{
	t_table	*t;

	t = table_call();
	while (get_long(&t->table_mtx, &t->threads_running) != t->data->nmr_philo);
}

bool	philo_died(t_philo *p)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&p->p_mtx, &p->full))
		return (false);
	elapsed = get_time(MILISECOND) - get_long(&p->p_mtx, &p->last_meal);
	time_to_die = table_call()->data->time_die / 1e3;//get_long??
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*set_killer_loose(void	*data)
{
	t_table	*t;
	int	i;

	t = (t_table *)data;
	ready_to_hunt();
	while(!sim_finished())
	{
		i = -1;
		while (++i < t->data->nmr_philo)
		{
			if (philo_died(t->philo + i))
			{
				print_status(DIED, t->philo + i);
				set_bool(&t->table_mtx, &t->end_simulation, true);
			}
		}
	}
	return (NULL);
}