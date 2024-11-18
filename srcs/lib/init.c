#include "../philosophers.h"

//singleton pattern
t_main	*main_call(void)
{
	static t_main	main;

	return (&main);
}

void	init_main(int argc, char **argv)
{
	main_call()->data = init_data(argc, argv);
}//not done

t_data	*init_data(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	t_data	*new;

	new = (t_data *)malloc(sizeof(t_data));
	new->nmr_philo = ft_atoi(argv[1]);
	new->time_die = ft_atoi(argv[2]);
	new->time_eat = ft_atoi(argv[3]);
	new->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		new->nmr_meals = ft_atoi(argv[5]);
	else
		new->nmr_meals = NULL;
	return (new);
}