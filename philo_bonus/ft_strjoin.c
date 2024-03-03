/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:01:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/03/03 12:14:20 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	cpy = (char *)malloc((i + 1) * sizeof(char));
	if (cpy == NULL)
		return (NULL);
	while (j < i)
	{
		cpy[j] = s1[j];
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstring;
	int		i;
	int		j;
	int		s1len;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (free(s1), ft_strdup(s2));
	s1len = ft_strlen(s1);
	newstring = (char *)malloc((s1len + ft_strlen(s2) + 1) * sizeof(char));
	if (newstring == NULL)
		return (free(s1), NULL);
	while (s1[i])
	{
		newstring[i] = s1[i];
		i++;
	}
	while (s2[j])
		newstring[i++] = s2[j++];
	newstring[i] = '\0';
	return (free(s1), newstring);
}

void	killchildsandexit(t_vars **vars)
{
	int	i;

	i = 0;
	sem_close((*vars)->semaphore);
	sem_close((*vars)->print_sem);
	sem_unlink("/my_semaphore");
	sem_unlink("/my_semaphore1");
	while ((*vars) && i < (*vars)->n_philos)
		kill((*vars)->philos[i++].philo, SIGKILL);
	free((*vars)->philos);
	free((*vars));
	exit(0);
}

int	waitforchilds(t_vars **vars)
{
	int	status;
	int	i;

	i = 0;
	while (waitpid((*vars)->philos[i].philo, &status, 0) != -1)
	{
		if (status != 0)
		{
			print_died(*vars, i);
			killchildsandexit(vars);
		}
		if (i == (*vars)->n_philos)
			i = 0;
		i++;
	}
	killchildsandexit(vars);
	return (1);
}
