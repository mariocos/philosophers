#include "philosophers.h"

void	print_status(t_philo_status code, t_philo *p)
{
	long	time;

	time = get_time(MILISECOND) - get_long(&p->table->table_mtx, &p->table->init_time);
	if (get_bool(&p->p_mtx, &p->is_full))
		return ;

	safe_mutex_handle(&p->table->print_mtx, LOCK);
	if ((code == TAKE_FIRST_FORK || code == TAKE_SECOND_FORK) && !sim_finished(p->table))
		printf("%-6ld philosopher %d has taken a fork\n", time, p->philo_id);
	else if (code == EATING && !sim_finished(p->table))
		printf("%-6ld philosopher %d is eating\n", time, p->philo_id);
	else if (code == SLEEPING && !sim_finished(p->table))
		printf("%-6ld philosopher %d is sleeping\n", time, p->philo_id);
	else if (code == THINKING && !sim_finished(p->table))
		printf("%-6ld philosopher %d is thinking\n", time, p->philo_id);
	else if (code == DIED && !sim_finished(p->table))
		printf("%-6ld philosopher %d has died\n", time, p->philo_id);
	safe_mutex_handle(&p->table->print_mtx, UNLOCK);
}