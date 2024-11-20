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
	long	time_die;
	long	time_eat;
	long	time_sleep;
	int		nmr_philo;
	int		nmr_meals;
}		t_data;

typedef struct	s_fork
{
	t_mtx	fork;
	int		fork_id;
}			t_fork;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				n_meals;
	bool			full;
	t_mtx			p_mtx;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thr_id;
}			t_philo;

typedef struct s_table
{
	// t_fork			*fork_pool;
	t_data			*data;
	long			init_time;
	bool			end_simulation;
	bool			ready_to_start;
	t_fork			*forks;
	t_philo			*philo;
	t_mtx			table_mtx;
	t_mtx			print_mtx;
}	t_table;


void	ft_err(char *err_msg);

// lib
int	ft_atoi(const char *str);
int	ft_isdigit(int c);

//init
t_data	*init_data(int argc, char **argv);
void	init_table(int argc, char **argv);
t_table	*table_call(void);

//safe
void	safe_mutex_handle(t_mtx *mtx, t_action code);
void	*safe_malloc(size_t size);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_action code);

//get_set GO!
bool	sim_finished(void);
long	get_long(t_mtx *mtx, long *dest);
void	set_long(t_mtx *mtx, long *dest, long value);
bool	get_bool(t_mtx *mtx, bool *dest);
void	set_bool(t_mtx *mtx, bool *dest, bool value);

//time 
long	get_time(t_time_code code);
void	good_sleep(long usec);


//status
void	print_status(t_philo_status code, t_philo *p);

//dinner
void	*dinner_simulation(void *data);
void	dinner_start(void);
void	wait_all_threads(void);
void	eat(t_philo *p);
void	think(t_philo *p);



#endif