#include "philosophers.h"

void	*safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		ft_err("critical error has occured\n");
	return (ret);
}


void	safe_mutex_handle(t_mtx *mtx, t_action code)
{
	int	i;

	if (code == LOCK)
		i = pthread_mutex_lock(mtx);
	else if (code == UNLOCK)
		i = pthread_mutex_unlock(mtx);
	else if (code == INIT)
		i = pthread_mutex_init(mtx, NULL);
	else if (code == DESTROY)
		i = pthread_mutex_destroy(mtx);
	else
		err("check your code dude you frickde up\n");//debug option maybe take away later
	if (i != 0)
		err("there has been a crit error in the threads function\n");
}


