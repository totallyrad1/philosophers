/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:52:47 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/27 22:29:05 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long get_time()
{
	struct timeval time;
	
	if(gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

static void init(char **av, t_vars **vars)
{
	int	i;

	i = 0;
	*vars = malloc(sizeof(t_vars));
	if (!*vars)
		exit(1);
	(*vars)->n_philos = ft_atoi(av[1]);
	(*vars)->time_to_die = ft_atoi(av[2]);
	(*vars)->time_to_eat = ft_atoi(av[3]);
	(*vars)->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		(*vars)->n_times_must_eat = ft_atoi(av[5]);
	else
		(*vars)->n_times_must_eat = -1;
}

int	main(int ac, char **av)
{
	t_vars	*vars;
	
	if (ac != 5 && ac != 6)
	{
		printf("invalid arguments\n");
		return (1);
	}
	init(av, &vars);
	if((vars) && !init_philos(&vars))
	{
		free(vars);
		return (1);
	}
}
