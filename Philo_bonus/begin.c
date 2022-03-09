/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:19:13 by akhachat          #+#    #+#             */
/*   Updated: 2022/02/14 19:08:51 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*love_of_thanos(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		sem_wait(philo->sem->lock);
		if (gettime() - philo->last_eat > philo->args->die_time)
		{
			message(philo, "died");
			kill(0, SIGINT);
			return (NULL);
		}
		sem_post(philo->sem->lock);
		usleep(1000);
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->sem->forks);
	message(philo, "has taken a fork");
	message(philo, "has taken a fork");
	philo->last_eat = gettime();
	message(philo, "is eating");
	usleep(philo->args->eat_time * 1000);
	sem_post(philo->sem->forks);
}

void	sleeping_and_thinking(t_philo *philo)
{
	message(philo, "is sleeping. Shhhh!");
	usleep(philo->args->sleep_time * 1000);
	message(philo, "is thinking. Hmmmm~");
}

void	life(t_philo *philo)
{
	int			must_eat;
	pthread_t	thread_id;

	must_eat = philo->args->must_eat;
	philo->last_eat = gettime();
	pthread_create(&thread_id, NULL, &love_of_thanos, (void *)philo);
	while (must_eat != 0)
	{
		eating(philo);
		sleeping_and_thinking(philo);
		usleep(1000);
		if (must_eat != -1)
			must_eat--;
	}
	exit(0);
}
