/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:28:56 by akhachat          #+#    #+#             */
/*   Updated: 2021/10/10 20:02:32 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks_again(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->lock);
	printf("%lld: Philosopher %d has taken a left fork\n",
		gettime() - philo->first_time, philo->name + 1);
	pthread_mutex_unlock(philo->lock);
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->lock);
	printf("%lld: Philosopher %d has taken a right fork\n",
		gettime() - philo->first_time, philo->name + 1);
	pthread_mutex_unlock(philo->lock);
}

void	take_forks(t_philo *philo)
{
	if (philo->name % 2 == 0)
	{
		pthread_mutex_lock(philo->right);
		pthread_mutex_lock(philo->lock);
		printf("%lld: Philosopher %d has taken a right fork\n",
			gettime() - philo->first_time, philo->name + 1);
		pthread_mutex_unlock(philo->lock);
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->lock);
		printf("%lld: Philosopher %d has taken a left fork\n",
			gettime() - philo->first_time, philo->name + 1);
		pthread_mutex_unlock(philo->lock);
	}
	else
		take_forks_again(philo);
}

void	*infinity_war(void *ptr)
{
	int		i;
	t_args	*args;
	int		opt_arg;

	args = ptr;
	while (1)
	{
		i = 0;
		opt_arg = 0;
		while (i < args->philo_num)
		{
			if (love_of_thanos(args, &i, &opt_arg))
				return (NULL);
			i++;
		}
		if (opt_arg == args->philo_num)
		{
			printf("End of simulation, cos everyone ate enough)\n");
			return (NULL);
		}
	}
	return (NULL);
}

void	age_of_ultron(t_args *arg)
{
	int			i;
	pthread_t	thanos;

	i = 0;
	pthread_create(&thanos, NULL, infinity_war, (void *)arg);
	while (i < arg->philo_num)
	{
		pthread_create(&arg->philo[i].main_thread,
			NULL, life, (void *)&arg->philo[i]);
		i++;
	}
	pthread_join(thanos, NULL);
	pthread_mutex_destroy(&arg->message);
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc == 1)
		exit(0);
	if (ft_atoi(argv[1]) == 0)
		ft_error("Really? Let's take my project seriously)\n \
			There must be at least one philosopher\n");
	if ((argc != 5 && argc != 6) || parsing(argc, argv, &args) == 0)
		ft_error("Error: Argument\n");
	printf("welcome to the jungle\n");
	age_of_ultron(&args);
	free(args.philo);
	return (0);
}
