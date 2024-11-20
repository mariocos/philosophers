#include "../philosophers.h"

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

	i = 0;
	if (code == LOCK)
		i = pthread_mutex_lock(mtx);
	else if (code == UNLOCK)
		i = pthread_mutex_unlock(mtx);
	else if (code == INIT)
		i = pthread_mutex_init(mtx, NULL);
	else if (code == DESTROY)
		i = pthread_mutex_destroy(mtx);
	else
		ft_err("check your code dude you frickde up\n");//debug option maybe take away later
	if (i != 0)
		ft_err("there has been a crit error in the threads function\n");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_action code)
{
	int	i;

	i = 0;
	if (code == CREATE)
		i = pthread_create(thread, NULL, foo, data);
	else if (code == JOIN)
		i = pthread_join(*thread, NULL);
	else if (code == DETACH)
		i = pthread_detach(*thread);
	else
		ft_err("check your code dude your passing a wrong thing in safe thread handle\n");
	if (i != 0)
		ft_err("a critical threads error has occurred\n");

}
