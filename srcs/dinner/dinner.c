#include "../philosophers.h"

bool	sim_finished(void)
{
	t_table	*t;

	t = table_call();
	return (get_bool(&t->table_mtx, &t->end_simulation));
}

void	dinner_start(void)
{
	t_table	*t;
	int	i;

	t = table_call();
	i = -1;
	if (t->data->nmr_meals == 0)
		return ;
	else if (t->data->nmr_philo <= 1)
		safe_thread_handle(&t->philo[0].thr_id, lonely_philo, &t->philo[0], CREATE);
	else
	{
		while (++i < t->data->nmr_philo)
		{
			safe_thread_handle(&t->philo[i].thr_id, dinner_simulation, &t->philo[i], CREATE);
		}
	}
	safe_thread_handle(&t->killer, set_killer_loose, table_call(), CREATE);
	t->init_time = get_time(MILISECOND);
	set_bool(&t->table_mtx, &t->ready_to_start, true);
	safe_thread_handle(&t->killer, NULL, NULL, JOIN);
	i = -1;
	while (++i < t->data->nmr_philo)
		safe_thread_handle(&t->philo[i].thr_id, NULL, NULL, JOIN);
}

void	*dinner_simulation(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	wait_all_threads();
	set_long(&p->p_mtx, &p->last_meal, get_time(MILISECOND));
	increment_long(&table_call()->table_mtx, &table_call()->threads_running);

	while (!sim_finished())
	{
		if (get_bool(&p->p_mtx, &p->full))
			break;
		eat(p);
		print_status(SLEEPING, p);
		good_sleep(get_long(&table_call()->table_mtx, &table_call()->data->time_to_sleep));
		think(p);
	}
	return (NULL);
}

void	*lonely_philo(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	wait_all_threads();
	set_long(&p->p_mtx, &p->last_meal, get_time(MILISECOND));
	increment_long(&table_call()->table_mtx, &table_call()->threads_running);
	print_status(TAKE_FIRST_FORK, p);
	while (!sim_finished())
		usleep(200);
	return (NULL);
}