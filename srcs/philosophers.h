#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H


# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>

typedef pthread_mutex_t t_mtx;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}		t_philo_status;

typedef enum	e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}		t_time_code;

typedef enum e_action
{
	LOCK,
	UNLOCK,
	INIT,
	CREATE,
	DESTROY,
	JOIN,
	DETACH,
}	t_action;


typedef struct s_data
{
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long		nmr_philo;
	long		max_meals;
}		t_data;

typedef struct	s_fork
{
	t_mtx	fork_mtx;
	int		fork_id;
}			t_fork;

typedef struct s_philo
{
	int				philo_id;
	long			last_meal_time;
	long				n_meals;
	bool			is_full;
	t_mtx			p_mtx;
	t_fork			*first_fork;
	t_fork			*scnd_fork;
	struct s_table	*table;
	pthread_t		thr_id;
}			t_philo;

typedef struct s_table
{
	t_data			*data;
	long			init_time;
	long			threads_running;
	bool			end_simulation;
	bool			ready_to_start;
	t_fork			*forks;
	t_philo			*philo;
	t_mtx			table_mtx;
	t_mtx			print_mtx;
	pthread_t		killer;
}	t_table;

//time
long	get_time(t_time_code code);
void	good_sleep(long usec, t_table *t);

//get_set GO!
bool	sim_finished(t_table *t);
bool	get_bool(t_mtx *mtx, bool *dest);
void	set_bool(t_mtx *mtx, bool *dest, bool value);

long	get_long(t_mtx *mtx, long *dest);
void	set_long(t_mtx *mtx, long *dest, long value);
void	increment_long(t_mtx *mtx, long *dest);

//dinner
void	eat(t_philo *p);
void	think(t_philo *p, bool flag);
void	dinner_start(t_table *t);


//print
void	print_status(t_philo_status code, t_philo *p);

//init
void	init_table(int argc, char **argv, t_table *t);
t_data	*init_data(int argc, char **argv);
void	philo_init(t_table *t);
void	assign_forks(t_philo *p, t_fork *forks, int	i);

//safe
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_action code);
void	safe_mutex_handle(t_mtx *mtx, t_action code);
void	*safe_malloc(size_t size);

//lib
int	ft_atoi(const char *str);

//err
void	ft_err(char *err_msg);
void	clean(t_table *t);


//the killer
void	*set_killer_loose(void	*data);



#endif