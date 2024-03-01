/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:54:09 by asnaji            #+#    #+#             */
/*   Updated: 2024/03/01 13:21:01 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void killchildsandexit(t_vars **vars)
{
	int	i;

	i = 0;
	while(i < (*vars)->n_philos)
		kill((*vars)->philos[i++].philo, SIGKILL);
	exit(0);
}

void *monitor(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(RAD)
	{
		if ((get_time() - philo->lasttime_ate) > philo->vars->time_to_die
				&& philo->eating_count != philo->vars->n_times_must_eat)
				exit(1);
	}
	return (NULL);
}

void	updatevalues(t_philo **philo)
{
	(*philo)->lasttime_ate = get_time();
	(*philo)->eating_count++;
}

void routine(t_philo *philo)
{
	pthread_t monitorth;
	int i = 0;

	while(RAD)
	{
		sem_wait(philo->vars->semaphore);
		print_tookfork(philo);
		sem_wait(philo->vars->semaphore);
		print_tookfork(philo);
		philo->lasttime_ate = get_time();
		print_eating(philo);
		philo->eating_count++;
		sem_post(philo->vars->semaphore);
		sem_post(philo->vars->semaphore);
		if (philo->eating_count == philo->vars->n_times_must_eat)
			exit(0);
		print_sleeping(philo);
		print_thinking(philo);
		if(i == 0)
		{
			pthread_create(&monitorth ,NULL, monitor, philo);
			pthread_detach(monitorth);
			i = 1;
		}
	}
}

int init_philos(t_vars **vars)
{
	int i;
	pid_t	id;
	int status;

	i = 0;
	(*vars)->semaphore = sem_open("WTF", O_CREAT, (*vars)->n_philos);
	(*vars)->print_sem = sem_open("print_sem", O_CREAT, 0, 1);
	(*vars)->philos = malloc(sizeof(t_philo) * (*vars)->n_philos);
	if (!(*vars)->philos)
		return (0);
	(*vars)->inittime =  get_time();
	while (i < (*vars)->n_philos)
	{
		(*vars)->philos[i].philoindex = i + 1;
		(*vars)->philos[i].vars = *vars;
		id = fork();
		(*vars)->philos[i].philo = id;
		if(id == 0)
		{
			routine(&(*vars)->philos[i]);
		}
		i++;
	}
	i = 0;
	while(waitpid((*vars)->philos[i].philo, &status, 0) != -1)
	{
		if(status != 0)
		{
			print_died(*vars, i);
			killchildsandexit(vars);
		}
		if(i == (*vars)->n_philos)
			i = 0;
		i++;
	}
	return (1);
}
