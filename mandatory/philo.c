/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:52:47 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/28 16:42:00 by asnaji           ###   ########.fr       */
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

static int init(char **av, t_vars **vars)
{
	int	i;

	i = 0;
	*vars = malloc(sizeof(t_vars));
	if (!*vars)
	{
		*vars = NULL;
		return (-1);
	}
	if (((*vars)->n_philos = ft_atoi(av[1])) <= 0)
		return (-1);
	if (((*vars)->time_to_die = ft_atoi(av[2])) <= 0)
		return (-1);
	if (((*vars)->time_to_eat = ft_atoi(av[3])) <= 0)
		return (-1);
	if (((*vars)->time_to_sleep = ft_atoi(av[4])) <= 0)
		return (-1);
	if (av[5])
	{
		if (((*vars)->n_times_must_eat = ft_atoi(av[5])) <= 0)
			return (-1);
	}
	else
		(*vars)->n_times_must_eat = -1;
	return (0);
}

void f()
{
	system("leaks philo > leaks");
}

int	main(int ac, char **av)
{
	t_vars	*vars;
	
	atexit(f);
	if ((ac != 5 && ac != 6 ) || checkargs(av) == -1)
	{
		printf("invalid arguments\n");
		return (1);
	}
	if (init(av, &vars) == -1)
	{
		if (vars)
			free(vars);
		return (1);
	}
	vars->monitoralive = 1;
	vars->everyoneate = vars->n_philos;
	if ((vars) && !init_philos(&vars))
		return (free_all(vars), 1);
}
