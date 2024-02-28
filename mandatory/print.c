/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:59:11 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/28 18:10:43 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_tookfork(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->print_mutex);
	printf("%ld %d has taken a fork\n", get_time() - philo->vars->inittime, philo->philoindex);
	pthread_mutex_unlock(&philo->vars->print_mutex);
}

void	print_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->print_mutex);
	printf("%ld %d is eating\n", get_time() - philo->vars->inittime, philo->philoindex);
	pthread_mutex_unlock(&philo->vars->print_mutex);
}

void	print_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->print_mutex);
	printf("%ld %d is sleeping\n", get_time() - philo->vars->inittime, philo->philoindex);
	pthread_mutex_unlock(&philo->vars->print_mutex);
}

void	print_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->print_mutex);
	printf("%ld %d is thinking\n", get_time() - philo->vars->inittime, philo->philoindex);
	pthread_mutex_unlock(&philo->vars->print_mutex);
}

void	print_died(t_vars *vars, int i)
{
	pthread_mutex_lock(&vars->print_mutex);
	printf("%ld philo %d died\n", get_time() - vars->inittime, vars->philos[i].philoindex);
}