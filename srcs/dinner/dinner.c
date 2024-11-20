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
		safe_thread_handle(&t->philo[0].thr_id, lonely_philo, &t->philo[0], CREATE);//maybe change
	else//create threds
	{
		while (++i < t->data->nmr_philo)
		{
			safe_thread_handle(&t->philo[i].thr_id, dinner_simulation, &t->philo[i], CREATE);
		}
	}
	//launch death checker
	safe_thread_handle(&t->killer, set_killer_loose, table_call(), CREATE);//not getting joined
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
	set_long(&p->p_mtx, &p->last_meal, get_time(MILISECOND));
	increment_long(&table_call()->table_mtx, &table_call()->threads_running);

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