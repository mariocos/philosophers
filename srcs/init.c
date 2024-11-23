/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariocos <mariocos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:21:31 by mariocos          #+#    #+#             */
/*   Updated: 2024/11/23 14:22:42 by mariocos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_forks(t_philo *p, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = p->table->data->nmr_philo;
	p->first_fork = &forks[i];
	p->scnd_fork = &forks[(i + 1) % philo_nbr];
	if (p->philo_id % 2 == 0)
	{
		p->first_fork = &forks[(i + 1) % philo_nbr];
		p->scnd_fork = &forks[i];
	}
}

void	philo_init(t_table *t)
{
	t_philo	*p;
	int		i;

	i = -1;
	while (++i < t->data->nmr_philo)
	{
		p = t->philo + i;
		p->is_full = false;
		p->philo_id = i + 1;
		p->n_meals = 0;
		p->table = t;
		assign_forks(p, t->forks, i);
	}
}

void	init_table(int argc, char **argv, t_table *t)
{
	int	i;

	i = -1;
	t->data = init_data(argc, argv);
	t->end_simulation = false;
	t->philo = safe_malloc(sizeof(t_philo) * t->data->nmr_philo);
	t->forks = safe_malloc(sizeof(t_fork) * t->data->nmr_philo);
	safe_mutex_handle(&t->table_mtx, INIT);
	safe_mutex_handle(&t->print_mtx, INIT);
	while (++i < t->data->nmr_philo)
	{
		safe_mutex_handle(&t->forks[i].fork_mtx, INIT);
		t->forks[i].fork_id = i;
	}
	philo_init(t);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*new;

	new = (t_data *)safe_malloc(sizeof(t_data));
	new->nmr_philo = ft_atoi(argv[1]);
	new->time_to_die = ft_atoi(argv[2]);
	new->time_to_eat = ft_atoi(argv[3]) * 1e3;
	new->time_to_sleep = ft_atoi(argv[4]) * 1e3;
	if (argc == 6)
		new->max_meals = ft_atoi(argv[5]);
	else
		new->max_meals = -1;
	return (new);
}
