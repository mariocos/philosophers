#include "../philosophers.h"

/*
lib functions
*/

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_atoi(const char *str)
{
	long	i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] != '\0' && str[i] == '-')
		ft_err("negative time not possible:(\n");
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && ft_isdigit(str[i]) && nbr < 2147483648)
		nbr = (nbr * 10) + (str[i++] - '0');
	if (nbr > 2147483647)
		ft_err("please use ints for time\n");
	return (nbr);
}

