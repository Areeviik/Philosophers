/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:28:29 by akhachat          #+#    #+#             */
/*   Updated: 2021/10/10 19:20:16 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_sems
{
	sem_t	*lock;
	sem_t	*forks;
	sem_t	*message;
}				t_sems;

typedef struct s_args
{
	int	philo_num;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	must_eat;
}			t_args;

typedef struct s_philo
{
	pid_t			pid;
	int				name;
	long long		first_time;
	long long		last_eat;
	t_sems			*sem;
	t_args			*args;

}				t_philo;

int			ft_atoi(char *str);
void		ft_error(char *str);
long long	gettime(void);
void		ft_usleep(int length);
void		create_sems(t_sems *sem, int len);
int			parsing(int argc, char **argv, t_args *args);
t_philo		*philos_init(t_args *args, t_sems *sem);
void		life(t_philo *philo);
void		message(t_philo *philo, char *str);
void		age_of_ultron(t_philo *philos);
void		*love_of_thanos(void *ptr);
void		eating(t_philo *philo);
void		sleeping_and_thinking(t_philo *philo);

#endif
