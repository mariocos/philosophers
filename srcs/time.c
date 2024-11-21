#include "philosophers.h"

long	get_time(t_time_code code)
{
	struct timeval	tv;
	if (-1 == gettimeofday(&tv, NULL))
		ft_err("a critical error has occurerd getting time\n");
	if (code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (code == MILISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		ft_err("check code theres been a problem\n");
	return (-1);
}

void	good_sleep(long usec, t_table *t)
{
	long	start;
	long	elapsed;
	long	remaining;
	(void)t;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (sim_finished(t))
			break;
		elapsed = get_time(MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(usec / 2);
		else
			while (get_time(MICROSECOND) - start < usec);
	}
}