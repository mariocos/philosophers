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

typedef enum e_action
{
	LOCK,
	UNLOCK,
	INIT,
	CREATE,
	DESTROY,
	JOIN,
}	t_action;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				n_meals;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thr_id;
}			t_philo;

typedef struct s_data
{
	long	time_die;
	long	time_eat;
	long	time_sleep;
	int		nmr_philo;
	int		nmr_meals;
}		t_data;

typedef struct s_table
{
	// t_fork			*fork_pool;
	t_data			*data;
	long			init_time;
	bool			end_simulation;
	t_fork			*forks;
	t_philo			*philo;
}	t_table;

typedef pthread_mutex_t t_mtx;

typedef struct	s_fork
{
	t_mtx	fork;
	int		fork_id;
}			t_fork;


void	ft_err(char *err_msg);

// lib
int	ft_atoi(const char *str);
int	ft_isdigit(int c);

//init
void	init_data(int argc, char **argv);
void	init_main(int argc, char **argv);
t_main	*main_call(void);










#endif