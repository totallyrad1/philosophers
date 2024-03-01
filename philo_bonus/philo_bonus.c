/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:19:12 by asnaji            #+#    #+#             */
/*   Updated: 2024/03/01 22:33:00 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

void	ft_sleep(int time)
{
	long	lhrba;

	lhrba = get_time();
	while (get_time() - lhrba < time)
		usleep(200);
}

static int	init(char **av, t_vars **vars)
{
	*vars = malloc(sizeof(t_vars));
	if (!*vars)
	{
		*vars = NULL;
		return (-1);
	}
	(*vars)->n_philos = ft_atoi(av[1]);
	(*vars)->time_to_die = ft_atoi(av[2]);
	(*vars)->time_to_eat = ft_atoi(av[3]);
	(*vars)->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		(*vars)->n_times_must_eat = ft_atoi(av[5]);
	else
		(*vars)->n_times_must_eat = -1;
	if ((*vars)->n_philos <= 0 || (*vars)->time_to_die <= 0
		|| (*vars)->time_to_eat <= 0 || (*vars)->time_to_sleep <= 0
		|| (av[5] && (*vars)->n_times_must_eat <= 0))
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	*vars;

	if ((ac != 5 && ac != 6) || checkargs(av) == -1)
	{
		printf("invalid arguments\n");
		return (1);
	}
	if (init(av, &vars) == -1)
	{
		printf("invalid arguments\n");
		if (vars)
			free(vars);
		return (1);
	}
	vars->everyoneate = vars->n_philos;
	if ((vars) && !init_philos(&vars))
		return (1);
}