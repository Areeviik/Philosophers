/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:28:56 by akhachat          #+#    #+#             */
/*   Updated: 2021/10/10 20:02:32 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping_and_thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	printf("%lld: Philosopher %d is sleeping, shhhh~!\n",
		gettime() - philo->first_time, philo->name + 1);
	pthread_mutex_unlock(philo->lock);
	ft_usleep(philo->sleep_time);
	pthread_mutex_lock(philo->lock);
	printf("%lld: Philosopher %d is thinking, hmmmm~\n",
		gettime() - philo->first_time, philo->name + 1);
	pthread_mutex_unlock(philo->lock);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	printf("%lld: Philosopher %d is eating\n",
		gettime() - philo->first_time, philo->name + 1);
	philo->last_eat = gettime();
	pthread_mutex_unlock(philo->lock);
	ft_usleep(philo->eat_time);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

void	*life(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (1)
	{
		take_forks(philo);
		eating(philo);
		philo->over++;
		sleeping_and_thinking(philo);
	}
	return (NULL);
}

int	love_of_thanos(t_args *args, int *i, int *opt_arg)
{
	if (args->philo->die_time < gettime() - (args->philo[*i].last_eat))
	{
		printf("%lld: O_ops, Philosopher %d died(((\n",
			gettime() - args->philo[*i].first_time, *i + 1);
		return (1);
	}
	if (args->philo[*i].over == args->philo[*i].must_eat_time)
	{
		usleep(100);
		++*opt_arg;
	}
	return (0);
}
