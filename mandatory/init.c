/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:25:37 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/27 22:31:33 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void ft_usleep(int time)
{
	long lhrba;

	lhrba = get_time();
	while(get_time() - lhrba < time)
		usleep(500);
}

void *routine(void *philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;
	if(philo->philoindex % 2 == 0)
		usleep(20);
	while(RAD)
	{
		pthread_mutex_lock(philo->leftfork);
		printf("%ld %d has taken a fork\n", get_time() - philo->vars->inittime, philo->philoindex);
		pthread_mutex_lock(philo->rightfork);
		printf("%ld %d has taken a fork\n", get_time() - philo->vars->inittime, philo->philoindex);
		printf("%ld %d is eating\n", get_time() - philo->vars->inittime, philo->philoindex);
		philo->lasttime_ate = get_time();
		philo->eating_count++;
		ft_usleep(philo->vars->time_to_eat);
		pthread_mutex_unlock(philo->leftfork);
		pthread_mutex_unlock(philo->rightfork);
		printf("%ld %d is sleeping\n", get_time() - philo->vars->inittime, philo->philoindex);
		ft_usleep(philo->vars->time_to_sleep);
		printf("%ld %d is thinking\n", get_time() - philo->vars->inittime, philo->philoindex);
	}
	return (NULL);
}

void initforks(t_vars **vars)
{
	int	i;

	i = 0;
	while((*vars) && i < (*vars)->n_philos)
	{
		(*vars)->philos[i].philoindex = i + 1;
		(*vars)->philos[i].vars = *vars;
		(*vars)->philos[i].leftfork = &(*vars)->forks[i];
		if(i != (*vars)->n_philos - 1)
			(*vars)->philos[i].rightfork = &(*vars)->forks[i + 1];
		else
			(*vars)->philos[i].rightfork = &(*vars)->forks[0];
		i++;
	}	
}

int init_philos(t_vars **vars)
{
	int	i;

	i = 0;
	while (i < (*vars)->n_philos)
	{
		if (pthread_mutex_init(&(*vars)->forks[i], NULL) != 0)
		{
			perror("pthread_mutex_init");
			return (0);
		}
		i++;
	}
	initforks(vars);
	i = 0;
	(*vars)->inittime = get_time();
	while (i < (*vars)->n_philos)
	{
		if (pthread_create(&(*vars)->philos[i].philo, NULL, routine, &(*vars)->philos[i]) != 0)
		{
			perror("pthread_create");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < (*vars)->n_philos)
	{
		if(pthread_join((*vars)->philos[i].philo, NULL) != 0)
		{
			perror("pthread_join");
			return (0);
		}
		i++;
	}
	return (1);
}
