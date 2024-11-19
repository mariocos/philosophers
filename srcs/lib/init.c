#include "../philosophers.h"

//singleton pattern
t_table	*table_call(void)
{
	static t_table	main;

	return (&main);
}

void	init_main(int argc, char **argv)
{
	table_call()->data = init_data(argc, argv);
	table_call()
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