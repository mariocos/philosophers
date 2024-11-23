/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:20:27 by mariocos          #+#    #+#             */
/*   Updated: 2024/11/23 14:20:51 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
