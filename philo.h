#ifndef PHILO_H
#define PHILO_H
# include <stdio.h> 
# include <stdlib.h> 
# include <unistd.h> 
# include <pthread.h> 
# include <limits.h>
# include <sys/time.h>
# define RAD 1
struct s_vars;

typedef struct s_philo
{
	pthread_t	philo;
	int			philoindex;
	long		lasttime_ate;
	int			eating_count;
	pthread_mutex_t *leftfork;
	struct s_vars	*vars;
	pthread_mutex_t *rightfork;
}				t_philo;

typedef struct s_vars
{
	int					n_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_times_must_eat;
	long				inittime;
	pthread_mutex_t		forks[200];
	t_philo				philos[200];
}				t_vars;


int	ft_atoi(const char *str);
int init_philos(t_vars **vars);
long get_time();

#endif