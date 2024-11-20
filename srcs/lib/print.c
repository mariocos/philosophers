#include "../philosophers.h"

void	print_status(t_philo_status code, t_philo *p)
{
	long	time;

	time = get_time(MILISECOND) - table_call()->init_time;
	if (get_bool(&p->p_mtx, &p->full))//thread safe??
		return ;

	safe_mutex_handle(&table_call()->print_mtx, LOCK);
	if ((code == TAKE_FIRST_FORK || code == TAKE_SECOND_FORK) && !sim_finished())
		printf("%-6ld philosopher %d has taken a fork\n", time, p->id);
	else if (code == EATING && !sim_finished())
		printf("%-6ld philosopher %d is eating\n", time, p->id);
	else if (code == SLEEPING && !sim_finished())
		printf("%-6ld philosopher %d is sleeping\n", time, p->id);
	else if (code == THINKING && !sim_finished())
		printf("%-6ld philosopher %d is thinking\n", time, p->id);
	else if (code == DIED && !sim_finished())
		printf("%-6ld philosopher %d has died\n", time, p->id);
	safe_mutex_handle(&table_call()->print_mtx, UNLOCK);
}