#include "philosophers.h"

void	think(t_philo *p, bool flag)
{
	long	t_sleep;
	long	t_think;
	long	t_eat;

	if (flag)
		print_status(THINKING, p);
	t_sleep = p->table->data->time_to_sleep;
	t_eat = p->table->data->time_to_eat;
	t_think = t_eat * 2 -t_sleep;
	if (t_think < 0)
		t_think = 0;
	good_sleep(t_think * 0.42, p->table);
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
	good_sleep(p->table->data->time_to_eat, p->table);
	if (p->table->data->max_meals > 0 && p->n_meals == p->table->data->max_meals)
		set_bool(&p->p_mtx, &p->is_full, true);
	safe_mutex_handle(&p->first_fork->fork_mtx, UNLOCK);
	safe_mutex_handle(&p->scnd_fork->fork_mtx, UNLOCK);
}

void	de_sync(t_philo *p)
{
	if (p->table->data->nmr_philo % 2 == 1)
	{
		if (p->philo_id % 2 == 1)
			think(p, false);
	}
}