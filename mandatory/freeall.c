/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:25:30 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/28 16:41:12 by asnaji           ###   ########.fr       */
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
	if (vars)
		free(vars);
	return (0);
}