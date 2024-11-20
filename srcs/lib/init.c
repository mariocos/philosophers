#include "../philosophers.h"

//singleton pattern
t_table	*table_call(void)
{
	static t_table	main;

	return (&main);
}

void	assign_forks(t_philo *p, t_fork *forks, int	i)
{
	int	philo_nbr;

	philo_nbr = table_call()->data->nmr_philo;
	p->scnd_fork = &forks[(i + 1) % philo_nbr];
	p->first_fork = &forks[i];
	if (p->id % 2 == 0)
	{
		p->scnd_fork = &forks[i];
		p->first_fork = &forks[(i + 1) % philo_nbr];
	}
}

void	philo_init(void)
{
	t_table	*t;
	t_philo	*p;
	int	i;

	t = table_call();
	i = -1;
	while (++i < t->data->nmr_philo)
	{
		p = t->philo + i;
		p->id = i + 1;
		p->full = false;
		p->n_meals = 0;
		safe_mutex_handle(&p->p_mtx, INIT);
		assign_forks(p, t->forks, i);
	}
}

void	init_table(int argc, char **argv)
{
	t_table *t;
	int	i;

	i = -1;
	t = table_call();
	t->threads_running = 0;
	t->end_simulation = false;
	t->ready_to_start = false;
	t->data = init_data(argc, argv);
	t->philo = safe_malloc(sizeof(t_philo) * t->data->nmr_philo);
	t->forks = safe_malloc(sizeof(t_fork) * t->data->nmr_philo);
	safe_mutex_handle(&t->table_mtx, INIT);
	safe_mutex_handle(&t->print_mtx, INIT);
	while (++i < t->data->nmr_philo)
	{
		safe_mutex_handle(&t->forks[i].fork, INIT);
		t->forks[i].fork_id = i;
	}
	philo_init();
}

t_data	*init_data(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	t_data	*new;

	new = (t_data *)safe_malloc(sizeof(t_data));
	new->nmr_philo = ft_atoi(argv[1]);
	new->time_die = ft_atoi(argv[2]) * 1e3;//for usleep already in microsecond
	new->time_eat = ft_atoi(argv[3]) * 1e3;
	new->time_sleep = ft_atoi(argv[4]) * 1e3;
	if (argc == 6)
		new->nmr_meals = ft_atoi(argv[5]);//might want to check if time is big enough
	else
		new->nmr_meals = -1;
	return (new);
}