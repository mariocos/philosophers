#include "philosophers.h"


int	main(int argc, char **argv)
{
	printf("hello\n");
	if (argc != 5 && argc != 6)
		ft_err("please call as follows: ./philosophers blablabla\n");// mi
	else
	{
		init_table(argc, argv);
		printf("nmbr of filo %d\n", table_call()->data->nmr_philo);
		dinner_start();
		write(1, "a", 1);

		//clean
	}
}