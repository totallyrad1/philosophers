/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:31:00 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/29 19:00:13 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_tookfork(t_philo *philo)
{
	printf("%ld %d has taken a fork\n", get_time()
		- philo->vars->inittime, philo->philoindex);
}

void	print_eating(t_philo *philo)
{
	printf("%ld %d is eating\n", get_time()
		- philo->vars->inittime, philo->philoindex);
	ft_sleep(philo->vars->time_to_eat);
}

void	print_sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time()
		- philo->vars->inittime, philo->philoindex);
	ft_sleep(philo->vars->time_to_sleep);
}

void	print_thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_time()
		- philo->vars->inittime, philo->philoindex);
}

void	print_died(t_vars *vars, int i)
{
	printf("%ld philo %d died\n", get_time()
		- vars->inittime, vars->philos[i].philoindex);
}