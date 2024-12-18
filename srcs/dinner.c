/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:13:47 by mariocos          #+#    #+#             */
/*   Updated: 2024/11/23 14:21:16 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	sim_finished(t_table *t)
{
	return (get_bool(&t->table_mtx, &t->end_simulation));
}

void	*lonely_philo(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	set_long(&p->table->table_mtx, &p->table->init_time, get_time(MILISECOND));
	set_long(&p->p_mtx, &p->last_meal_time, get_time(MILISECOND));
	print_status(TAKE_FIRST_FORK, p);
	while (!sim_finished(p->table))
		usleep(200);
	return (NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	set_long(&p->table->table_mtx, &p->table->init_time, get_time(MILISECOND));
	set_long(&p->p_mtx, &p->last_meal_time, get_time(MILISECOND));
	while (!sim_finished(p->table))
	{
		if (get_bool(&p->p_mtx, &p->is_full))
			break ;
		eat(p);
		print_status(SLEEPING, p);
		good_sleep(get_long(&p->table->table_mtx,
				&p->table->data->time_to_sleep), p->table);
		think(p, true);
	}
	return (NULL);
}

void	dinner_start(t_table *t)
{
	int	i;

	i = -1;
	if (get_long(&t->table_mtx, &t->data->max_meals) == 0)
		return ;
	else if (get_long(&t->table_mtx, &t->data->nmr_philo) <= 1)
		safe_thread_handle(&t->philo[0].thr_id,
			lonely_philo, &t->philo[0], CREATE);
	else
	{
		while (++i < t->data->nmr_philo)
			safe_thread_handle(&t->philo[i].thr_id,
				dinner_simulation, &t->philo[i], CREATE);
	}
	safe_thread_handle(&t->killer, set_killer_loose, t, CREATE);
	i = -1;
	while (++i < get_long(&t->table_mtx, &t->data->nmr_philo))
		safe_thread_handle(&t->philo[i].thr_id, NULL, NULL, JOIN);
	set_bool(&t->table_mtx, &t->end_simulation, true);
	safe_thread_handle(&t->killer, NULL, NULL, JOIN);
}
