/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:28:56 by akhachat          #+#    #+#             */
/*   Updated: 2022/02/14 19:07:17 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_sems(t_sems *sem, int len)
{
	sem_unlink("forks");
	sem_unlink("message");
	sem_unlink("lock");
	sem->forks = sem_open("forks", O_CREAT | O_RDWR, 0660, len / 2);
	sem->message = sem_open("message", O_CREAT | O_RDWR, 0660, 1);
	sem->lock = sem_open("lock", O_CREAT | O_RDWR, 0660, 1);
}

int	parsing(int argc, char **argv, t_args *args)
{
	args->philo_num = ft_atoi(argv[1]);
	args->die_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		args->must_eat = ft_atoi(argv[5]);
	else
		args->must_eat = -1;
	return (1);
}

t_philo	*philos_init(t_args *args, t_sems *sem)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * args->philo_num);
	while (i < args->philo_num)
	{
		philos[i].name = i + 1;
		philos[i].first_time = 0;
		philos[i].last_eat = 0;
		philos[i].sem = sem;
		philos[i].args = args;
		i++;
	}
	return (philos);
}
