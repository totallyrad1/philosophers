/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:25:37 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/28 16:34:57 by asnaji           ###   ########.fr       */
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
		usleep(200);
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
		if (philo->eating_count == philo->vars->n_times_must_eat)
		{
			philo->vars->everyoneate--;
			break;
		}
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
		(*vars)->philos[i].eating_count = 0;
		(*vars)->philos[i].lasttime_ate = get_time();
		(*vars)->philos[i].vars = *vars;
		(*vars)->philos[i].leftfork = &(*vars)->forks[i];
		if(i != (*vars)->n_philos - 1)
			(*vars)->philos[i].rightfork = &(*vars)->forks[i + 1];
		else
			(*vars)->philos[i].rightfork = &(*vars)->forks[0];
		i++;
	}	
}

int forksnphilos(t_vars **vars)
{
	int	i;

	i = 0;
	(*vars)->forks = malloc(sizeof(pthread_mutex_t) * (*vars)->n_philos);
	if (!(*vars)->forks)
		return (-1);
	(*vars)->philos = malloc(sizeof(t_philo) * (*vars)->n_philos);
	if (!(*vars)->philos)
		return(-1);
	return (1);
}

void manager(t_vars *vars)
{
	int	i;

	i = 0;
	while(RAD && vars->everyoneate > 0)
	{
		if(i == (vars)->n_philos)
			i = 0;
		if((get_time() - vars->philos[i].lasttime_ate) >= vars->time_to_die && vars->philos[i].eating_count != vars->n_times_must_eat)
		{
			printf("%ld philo %d died\n", get_time() - vars->inittime, vars->philos[i].philoindex);
			vars->monitoralive = 0;
			return ;
		}
		i++;
	}
}

int init_philos(t_vars **vars)
{
	int	i;

	i = 0;
	if(forksnphilos(vars) == -1)
		return (0);
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
		if(pthread_detach((*vars)->philos[i].philo) != 0)
		{
			perror("pthread_detach");
			return (0);
		}
		i++;
	}
	manager(*vars);
	return (1);
}
