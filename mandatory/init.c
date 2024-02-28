/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:25:37 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/28 19:32:11 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo->philoindex % 2 == 0)
		usleep(200);
	while (RAD)
	{
		pthread_mutex_lock(philo->leftfork);
		print_tookfork(philo);
		pthread_mutex_lock(philo->rightfork);
		print_tookfork(philo);
		print_eating(philo);
		updatevalues(&philo);
		pthread_mutex_unlock(philo->leftfork);
		pthread_mutex_unlock(philo->rightfork);
		if (philo->eating_count == philo->vars->n_times_must_eat)
		{
			philo->vars->everyoneate--;
			break ;
		}
		print_sleeping(philo);
		print_thinking(philo);
	}
	return (NULL);
}

int	initmutexes(t_vars **vars)
{
	int	i;

	i = 0;
	if (forksnphilos(vars) == -1)
		return (0);
	if (pthread_mutex_init(&(*vars)->print_mutex, NULL) != 0)
	{
		perror("pthread_mutex_init");
		return (0);
	}
	if (pthread_mutex_init(&(*vars)->lasttimeatemutex, NULL) != 0)
	{
		perror("pthread_mutex_init");
		return (0);
	}
	while (i < (*vars)->n_philos)
	{
		if (pthread_mutex_init(&(*vars)->forks[i], NULL) != 0)
		{
			perror("pthread_mutex_init");
			return (0);
		}
		i++;
	}
	return (initforks(vars));
}

int	detachthreads(t_vars **vars)
{
	int	i;

	i = 0;
	while (i < (*vars)->n_philos)
	{
		if (pthread_detach((*vars)->philos[i].philo) != 0)
		{
			perror("pthread_detach");
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philos(t_vars **vars)
{
	int	i;

	i = 0;
	if (initmutexes(vars) == 0)
		return (0);
	(*vars)->inittime = get_time();
	while (i < (*vars)->n_philos)
	{
		if (pthread_create(&(*vars)->philos[i].philo,
				NULL, routine, &(*vars)->philos[i]) != 0)
		{
			perror("pthread_create");
			return (0);
		}
		i++;
	}
	if (detachthreads(vars) == 0)
		return (0);
	manager(*vars);
	free_all(*vars);
	return (1);
}
