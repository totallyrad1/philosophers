/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:25:30 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/28 19:49:27 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	free_all(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars && vars->philos)
		free(vars->philos);
	i = 0;
	while (vars && vars->forks && i < vars->n_philos)
		pthread_mutex_destroy(&(vars->forks[i++]));
	if (vars && vars->forks)
		free(vars->forks);
	if (vars && &(vars->print_mutex))
		pthread_mutex_destroy(&(vars->print_mutex));
	if (vars && &(vars->lasttimeatemutex))
		pthread_mutex_destroy(&(vars->lasttimeatemutex));
	if (vars)
		free(vars);
	return (0);
}

void	manager(t_vars *vars)
{
	int	i;

	i = 0;
	while (RAD)
	{
		if (i == (vars)->n_philos)
			i = 0;
		pthread_mutex_lock(&vars->lasttimeatemutex);
		if (vars->everyoneate <= 0)
			return ;
		if ((get_time() - vars->philos[i].lasttime_ate) > vars->time_to_die
			&& vars->philos[i].eating_count != vars->n_times_must_eat)
		{
			print_died(vars, i);
			vars->monitoralive = 0;
			return ;
		}
		pthread_mutex_unlock(&vars->lasttimeatemutex);
		i++;
	}
}

int	forksnphilos(t_vars **vars)
{
	int	i;

	i = 0;
	(*vars)->forks = malloc(sizeof(pthread_mutex_t) * (*vars)->n_philos);
	if (!(*vars)->forks)
		return (-1);
	(*vars)->philos = malloc(sizeof(t_philo) * (*vars)->n_philos);
	if (!(*vars)->philos)
		return (-1);
	return (1);
}

int	initforks(t_vars **vars)
{
	int	i;

	i = 0;
	while ((*vars) && i < (*vars)->n_philos)
	{
		(*vars)->philos[i].philoindex = i + 1;
		(*vars)->philos[i].eating_count = 0;
		(*vars)->philos[i].lasttime_ate = get_time();
		(*vars)->philos[i].vars = *vars;
		(*vars)->philos[i].leftfork = &(*vars)->forks[i];
		if (i != (*vars)->n_philos - 1)
			(*vars)->philos[i].rightfork = &(*vars)->forks[i + 1];
		else
			(*vars)->philos[i].rightfork = &(*vars)->forks[0];
		i++;
	}
	return (1);
}
