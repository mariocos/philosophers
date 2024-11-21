#include "philosophers.h"

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

	set_long(&p->p_mtx, &p->last_meal_time, get_time(MILISECOND));

	increment_long(&p->p_mtx, &p->n_meals);

	print_status(EATING, p);

	good_sleep(get_long(&p->table->table_mtx, &p->table->data->time_to_sleep), p->table);
	if (p->table->data->max_meals > 0 && p->n_meals == p->table->data->max_meals)
		set_bool(&p->p_mtx, &p->is_full, true);
	safe_mutex_handle(&p->first_fork->fork_mtx, UNLOCK);
	safe_mutex_handle(&p->scnd_fork->fork_mtx, UNLOCK);
}