#include "../philosophers.h"

void	dinner_start(void)
{
	t_table	*t;
	int	i;

	t = table_call();
	i = -1;
	if (t->data->nmr_meals == 0)
		return ;
	else if (t->data->nmr_philo <= 1)
		return ;//maybe change
	else//create threds
	{
		while (++i < t->data->nmr_philo)
		{
			safe_thread_handle(&t->philo[i].thr_id, dinner_simulation, &t->philo[i], CREATE);
		}
	}
	t->init_time = get_time(MILISECOND);
	set_bool(&t->table_mtx, &t->ready_to_start, true);
	i = -1;
	while (++i < t->data->nmr_philo)//bit unsure
		safe_thread_handle(&t->philo[i].thr_id, NULL, NULL, JOIN);
}

void	*dinner_simulation(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	wait_all_threads();

	while (!sim_finished())
	{
		if (p->full)
			break;
		eat(p);
		print_status(SLEEPING, p);
		good_sleep(table_call()->data->time_sleep);
		think(p);
	}
	return (NULL);
}