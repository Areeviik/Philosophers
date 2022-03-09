/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:47:46 by akhachat          #+#    #+#             */
/*   Updated: 2022/02/11 16:47:52 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	age_of_ultron(t_philo *philos)
{
	int		i;
	int		status;
	int		size;

	i = 0;
	size = philos[0].args->philo_num;
	while (i < size)
	{
		philos[i].first_time = gettime();
		philos[i].pid = fork();
		if (philos[i].pid == 0)
			life(&philos[i]);
		else if (philos[i].pid < 0)
			ft_error("Error while oppening a fork");
		i++;
	}
	i = 0;
	while (i++ < size)
		waitpid(philos[i].pid, &status, 0);
	printf("End of simulation, cos everyone ate enough)\n");
}

int	main(int argc, char **argv)
{
	t_philo		*philos;
	t_args		args;
	t_sems		sem;

	if ((argc != 5 && argc != 6) || (parsing(argc, argv, &args) == 0))
		ft_error("Error: Argument\n");
	if (ft_atoi(argv[1]) == 0)
		ft_error("Really? Let's take my project seriously)\n \
			There must be at least one philosopher\n");
	create_sems(&sem, args.philo_num);
	philos = philos_init(&args, &sem);
	age_of_ultron(philos);
	sem_close(sem.forks);
	sem_close(sem.message);
	sem_close(sem.lock);
	free(philos);
	return (0);
}
