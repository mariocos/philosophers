/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:23:09 by mariocos          #+#    #+#             */
/*   Updated: 2024/11/23 14:23:44 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_died(t_philo *p)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&p->p_mtx, &p->is_full))
		return (false);
	elapsed = get_time(MILISECOND) - get_long(&p->p_mtx, &p->last_meal_time);
	time_to_die = p->table->data->time_to_die;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*set_killer_loose(void	*data)
{
	t_table	*t;
	int		i;

	t = (t_table *)data;
	while (!sim_finished(t))
	{
		i = -1;
		while (++i < t->data->nmr_philo)
		{
			if (philo_died(t->philo + i))
			{
				print_status(DIED, t->philo + i);
				set_bool(&t->table_mtx, &t->end_simulation, true);
			}
		}
	}
	return (NULL);
}
