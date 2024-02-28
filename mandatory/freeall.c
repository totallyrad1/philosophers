/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:25:30 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/28 18:24:58 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int free_all(t_vars *vars)
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