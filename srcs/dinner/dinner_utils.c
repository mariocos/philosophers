#include "../philosophers.h"

void	think(t_philo *p)
{
	print_status(THINKING, p);
}

void	eat(t_philo *p)
{
	safe_mutex_handle(&p->first_fork->fork_mtx, LOCK);
	print_status(TAKE_FIRST_FORK, p);
	safe_mutex_handle(&p->scnd_fork->fork_mtx, LOCK);
	print_status(TAKE_SECOND_FORK, p);

	set_long(&p->p_mtx, &p->last_meal, get_time(MILISECOND));
	p->n_meals++;
	print_status(EATING, p);
	good_sleep(get_long(&table_call()->table_mtx, &table_call()->data->time_to_sleep));
	if (table_call()->data->nmr_meals > 0 && p->n_meals == table_call()->data->nmr_meals)
		set_bool(&p->p_mtx, &p->full, true);
	safe_mutex_handle(&p->first_fork->fork_mtx, UNLOCK);
	safe_mutex_handle(&p->scnd_fork->fork_mtx, UNLOCK);
}

void	wait_all_threads(void)
{
	while (!get_bool(&table_call()->table_mtx, &table_call()->ready_to_start));
}