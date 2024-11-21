#include "philosophers.h"

bool	sim_finished(t_table *t)
{
	return (get_bool(&t->table_mtx, &t->end_simulation));
}

void	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = value;
	safe_mutex_handle(mtx, UNLOCK);
}

bool	get_bool(t_mtx *mtx, bool *dest)
{
	bool	ret;

	safe_mutex_handle(mtx, LOCK);
	ret = *dest;
	safe_mutex_handle(mtx, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mtx, long *dest, long value)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = value;
	safe_mutex_handle(mtx, UNLOCK);
}

void	increment_long(t_mtx *mtx, long *dest)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = *dest + 1;
	safe_mutex_handle(mtx, UNLOCK);
}


long	get_long(t_mtx *mtx, long *dest)
{
	long	ret;

	safe_mutex_handle(mtx, LOCK);
	ret = *dest;
	safe_mutex_handle(mtx, UNLOCK);
	return (ret);
}
