#include "../philosophers.h"

void	ft_err(char *err_msg)
{
	int	i;
	
	i = -1;
	while (err_msg[++i])
		write(1, &err_msg[i], 1);
//	free_all();//missing imp
	exit(1);
}