#include "../philosophers.h"

//singleton pattern
t_table	*table_call(void)
{
	static t_table	main;

	return (&main);
}

void	init_table(int argc, char **argv)
{
	t_table *t;
	int	i;

	i = -1
	t = table_call();
	t->end_simulation = false;
	t->data = init_data(argc, argv);
	t->philo = safe_malloc(sizeof(t_philo) * t->data->nmr_philo);
	t->forks = safe_malloc(sizeof(t_fork) * t->data->nmr_philo);
	while (++i < t->data->nmr_philo)
	{
		safe_mutex_handle(&t->forks[i].fork, INIT);
		t->forks[i].fork_id = i;
	}
}//not done

t_data	*init_data(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	t_data	*new;

	new = (t_data *)safe_malloc(sizeof(t_data));
	new->nmr_philo = ft_atoi(argv[1]) * 1e3;//for usleep already in microsecond
	new->time_die = ft_atoi(argv[2]) * 1e3;
	new->time_eat = ft_atoi(argv[3]) * 1e3;
	new->time_sleep = ft_atoi(argv[4]) * 1e3;
	if (argc == 6)
		new->nmr_meals = ft_atoi(argv[5]);//might want to check if time is big enough
	else
		new->nmr_meals = -1;
	return (new);
}