/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:52:47 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/28 19:39:13 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	updatevalues(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->vars->lasttimeatemutex);
	(*philo)->lasttime_ate = get_time();
	(*philo)->eating_count++;
	pthread_mutex_unlock(&(*philo)->vars->lasttimeatemutex);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

void	ft_usleep(int time)
{
	long	lhrba;

	lhrba = get_time();
	while (get_time() - lhrba < time)
		usleep(500);
}

static int	init(char **av, t_vars **vars)
{
	int	i;

	i = 0;
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
		if (vars)
			free(vars);
		return (1);
	}
	vars->monitoralive = 1;
	vars->everyoneate = vars->n_philos;
	if ((vars) && !init_philos(&vars))
		return (free_all(vars), 1);
}
