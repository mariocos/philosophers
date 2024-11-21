#include "philosophers.h"


int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		ft_err("please call as follows: ./philosophers time_to_die time_to_eat time_to_sleep min_meals(optional)\n");
	else
	{
		init_table(argc, argv, &table);
		dinner_start(&table);
		clean(&table);
		exit(0);
	}
}