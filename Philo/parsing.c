/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:28:56 by akhachat          #+#    #+#             */
/*   Updated: 2021/10/10 20:02:32 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parce_init(t_args **arg, int argc, pthread_mutex_t	*forks, int flag)
{
	int				i;

	i = 0;
	while (i < (*arg)->philo_num)
	{
		if (argc == 6 && flag && i == (*arg)->philo_num - 1)
			(*arg)->philo[i].name = i - 1;
		else
			(*arg)->philo[i].name = i;
		(*arg)->philo[i].lock = &(*arg)->message;
		(*arg)->philo[i].last_eat = (*arg)->gettime;
		(*arg)->philo[i].first_time = (*arg)->gettime;
		(*arg)->philo[i].total_eat = 0;
		(*arg)->philo[i].left = &forks[i];
		(*arg)->philo[i].right = &forks[(i + 1) % (*arg)->philo_num];
		(*arg)->philo[i].die_time = (*arg)->die;
		(*arg)->philo[i].eat_time = (*arg)->eat;
		(*arg)->philo[i].sleep_time = (*arg)->sleep;
		if (argc == 6)
			(*arg)->philo[i].must_eat_time = (*arg)->must_eat;
		else
			(*arg)->philo[i].must_eat_time = (*arg)->must_eat;
		(*arg)->philo[i].over = 0;
		i++;
	}
}

int	check(int argc, t_args **arg)
{
	if (argc == 6 && (*arg)->philo_num % 2 == 1)
	{
		return (1);
	}
	return (0);
}

int	parsing(int argc, char **argv, t_args *arg)
{
	int				i;
	pthread_mutex_t	*forks;

	arg->gettime = gettime();
	arg->philo_num = ft_atoi(argv[1]);
	arg->die = ft_atoi(argv[2]);
	arg->eat = ft_atoi(argv[3]);
	arg->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->must_eat = ft_atoi(argv[5]);
	else
		arg->must_eat = -1;
	arg->philo = malloc(sizeof(t_philo) * arg->philo_num);
	if (arg->philo == NULL)
		return (0);
	if (check(argc, &arg))
		arg->philo_num++;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	i = -1;
	while (++i < arg->philo_num)
		pthread_mutex_init(&forks[i], NULL);
	pthread_mutex_init(&arg->message, NULL);
	parce_init(&arg, argc, forks, check(argc, &arg));
	return (1);
}
