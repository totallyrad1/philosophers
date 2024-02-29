/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:11:57 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/29 19:10:12 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h> 
# include <stdlib.h> 
# include <unistd.h> 
# include <pthread.h> 
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>

# define RAD 1

typedef struct s_philo
{
	pid_t			philo;
	int				philoindex;
	long			lasttime_ate;
	int				eating_count;
	struct s_vars	*vars;
}				t_philo;

typedef struct s_vars
{
	int					n_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_times_must_eat;
	long				inittime;
	t_philo				*philos;
	sem_t				*semaphore;
	int					everyoneate;
}				t_vars;

long	get_time(void);
void	ft_sleep(int time);
int	checkargs(char **av);
int	ft_atoi(const char *str);
int init_philos(t_vars **vars);

void	print_tookfork(t_philo *philo);
void	print_eating(t_philo *philo);
void	print_sleeping(t_philo *philo);
void	print_thinking(t_philo *philo);
void	print_died(t_vars *vars, int i);

#endif