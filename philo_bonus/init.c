/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:54:09 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/29 19:27:08 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *monitor(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(RAD)
	{
		if ((get_time() - philo->lasttime_ate) > philo->vars->time_to_die
				&& philo->eating_count != philo->vars->n_times_must_eat)
			{
				print_died(philo->vars, philo->philoindex);
				exit(1);
			}
		if(philo->eating_count == philo->vars->n_times_must_eat)
			exit(0);
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

	if(philo->philoindex % 2 == 0)
		usleep(200);
	(philo)->lasttime_ate = get_time();
	pthread_create(&monitorth ,NULL, monitor, philo);
	pthread_detach(monitorth);
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
		print_sleeping(philo);
		print_thinking(philo);
	}
}

int init_philos(t_vars **vars)
{
	int i;
	pid_t	id;
	int status;

	i = 0;
	(*vars)->semaphore = sem_open("WTF", O_CREAT, 0, (*vars)->n_philos);
	(*vars)->philos = malloc(sizeof(t_philo) * (*vars)->n_philos);
	if (!(*vars)->philos)
		return (0);
	(*vars)->inittime =  get_time();
	while(i < (*vars)->n_philos)
	{
		(*vars)->philos[i].vars = *vars;
		(*vars)->philos[i].philoindex = i + 1;
		id = fork();
		(*vars)->philos[i].philo = id;
		if(id == 0)
			routine(&(*vars)->philos[i]);
		else
			i++;
	}
	i = 0;
	while(waitpid((*vars)->philos[i].philo, &status, 0) != -1)
	{
		if(status == 1)
			exit(0);
		if(i == (*vars)->n_philos)
			i = 0;
		i++;
	}
	return (1);
}
