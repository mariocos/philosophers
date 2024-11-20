#include "../philosophers.h"

void	think(t_philo *p)
{
	print_status(THINKING, p);
}

void	eat(t_philo *p)
{
	safe_mutex_handle(&p->left_fork->fork, LOCK);
	print_status(TAKE_FIRST_FORK, p);
	safe_mutex_handle(&p->right_fork->fork, LOCK);
	print_status(TAKE_SECOND_FORK, p);

	set_long(&p->p_mtx, &p->last_meal, get_time(MILISECOND));
	p->n_meals++;
	good_sleep(table_call()->data->time_eat);
	if (table_call()->data->nmr_meals > 0 && p->n_meals == table_call()->data->nmr_meals)
		set_bool(&p->p_mtx, &p->full, true);
	safe_mutex_handle(&p->left_fork->fork, UNLOCK);
	safe_mutex_handle(&p->right_fork->fork, UNLOCK);
}

void	wait_all_threads(void)
{
	while (!get_bool(&table_call()->table_mtx, &table_call()->ready_to_start));
}