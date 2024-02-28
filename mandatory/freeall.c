/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:25:30 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/28 16:28:06 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int free_all(t_vars *vars, int exitstatus)
{
	int	i;

	i = 0;
	if (vars && vars->philos)
		free(vars->philos);
	i = 0;
	while (vars && vars->forks && &(vars->forks[i]))
		pthread_mutex_destroy(&(vars->forks[i]));
	if (vars && vars->forks)
		free(vars->forks);
	if (vars)
		free(vars);
	return (exitstatus);
}