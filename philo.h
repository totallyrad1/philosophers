/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:32:23 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/28 21:44:29 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h> 
# include <stdlib.h> 
# include <unistd.h> 
# include <pthread.h> 
# include <limits.h>
# include <sys/time.h>

# define RAD 1

struct	s_vars;

typedef struct s_philo
{
	pthread_t		philo;
	int				philoindex;
	long			lasttime_ate;
	int				eating_count;
	pthread_mutex_t	*leftfork;
	struct s_vars	*vars;
	pthread_mutex_t	*rightfork;
}				t_philo;

typedef struct s_vars
{
	int					n_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_times_must_eat;
	long				inittime;
	pthread_mutex_t		*forks;
	t_philo				*philos;
	int					ended;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		lasttimeatemutex;
	int					monitoralive;
	int					everyoneate;
}				t_vars;

int		ft_atoi(const char *str);
int		init_philos(t_vars **vars);
long	get_time(void);
int		checkargs(char **av);
int		free_all(t_vars *vars);
void	ft_usleep(int time);
void	manager(t_vars *vars, int i);
int		forksnphilos(t_vars **vars);
int		initforks(t_vars **vars);
void	updatevalues(t_philo **philo);

void	print_tookfork(t_philo *philo);
void	print_eating(t_philo *philo);
void	print_sleeping(t_philo *philo);
void	print_thinking(t_philo *philo);
void	print_died(t_vars *vars, int i);

#endif