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

typedef enum e_dest
{
	TABLE,
	PHILO,
}	t_dest;

typedef enum e_action
{
	LOCK,
	UNLOCK,
	INIT,
	CREATE,
	DESTROY,
	JOIN,
}	t_action;

typedef enum e_status
{
	WAIT,
	START,
	STOP,
	FINIT,
	LEFT,
	RIGHT,
	BOTH,
}	t_status;


typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				n_meals;
	t_status		status;
	struct s_philo	*left;
	struct s_philo	*right;
	pthread_t		thr;
	pthread_mutex_t	fork;
	pthread_mutex_t	mtx_philo;
}			t_philo;

typedef struct s_data
{
	long	time_die;
	long	time_eat;
	long	time_sleep;
	int		nmr_philo;
	int		nmr_meals;
}		t_data;

typedef struct s_main
{
	// t_fork			*fork_pool;
	t_status		main_status;
	long			init_time;
	t_data			*data;
	t_philo			*philo;
	pthread_t		sys_thr;
	pthread_mutex_t	sys_mutex;
}	t_main;


void	ft_err(char *err_msg);

// lib
int	ft_atoi(const char *str);
int	ft_isdigit(int c);

//init
void	init_data(int argc, char **argv);
void	init_main(int argc, char **argv);
t_main	*main_call(void);










#endif