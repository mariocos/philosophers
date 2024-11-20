#include "philosophers.h"


int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		ft_err("please call as follows: ./philosophers blablabla\n");// mi
	else
	{
		init_table(argc, argv);
		dinner_start();

		//clean
	}
}