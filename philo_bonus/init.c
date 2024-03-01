/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:54:09 by asnaji            #+#    #+#             */
/*   Updated: 2024/03/01 16:24:28 by asnaji           ###   ########.fr       */
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

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	philo->lasttime_ate = get_time();
	if (philo->philoindex % 2 == 0)
		usleep(500);
	while(RAD)
	{
		sem_wait(philo->vars->semaphore);
		print_tookfork(philo);
		sem_wait(philo->vars->semaphore);
		print_tookfork(philo);
		print_eating(philo);
		updatevalues(&philo);
		sem_post(philo->vars->semaphore);
		sem_post(philo->vars->semaphore);
		if (philo->eating_count == philo->vars->n_times_must_eat)
			exit(0);
		print_sleeping(philo);
		print_thinking(philo);
	}
}

void chhild(t_philo *philo)
{
	pthread_t monitorth;
	pthread_t slave;

	pthread_create(&slave ,NULL, routine, philo);
	pthread_create(&monitorth ,NULL, monitor, philo);
	pthread_join(slave, NULL);
}

int init_philos(t_vars **vars)
{
	int i;
	int status;

	i = 0;
	(*vars)->semaphore = sem_open("/my_semaphore", O_CREAT, (*vars)->n_philos);
	(*vars)->print_sem = sem_open("/my_semaphore1", O_CREAT, 0, 1);
	(*vars)->philos = malloc(sizeof(t_philo) * (*vars)->n_philos);
	if (!(*vars)->philos)
		return (0);
	(*vars)->inittime =  get_time();
	while (i < (*vars)->n_philos)
	{
		(*vars)->philos[i].philoindex = i + 1;
		(*vars)->philos[i].vars = *vars;
		(*vars)->philos[i].philo = fork();
		if((*vars)->philos[i].philo == 0)
			chhild(&(*vars)->philos[i]);
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
