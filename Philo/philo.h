/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:28:29 by akhachat          #+#    #+#             */
/*   Updated: 2021/10/10 19:20:16 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	unsigned long long	die_time;
	unsigned long long	eat_time;
	unsigned long long	sleep_time;
	int					must_eat_time;
	int					death_check;
	int					over;
	long long			first_time;
	int					name;
	unsigned long long	last_eat;
	int					total_eat;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	pthread_mutex_t		*lock;
	pthread_t			main_thread;
}	t_philo;

typedef struct s_args
{
	int					philo_num;
	unsigned long long	die;
	unsigned long long	eat;
	unsigned long long	sleep;
	int					must_eat;
	unsigned long long	gettime;
	pthread_mutex_t		message;
	t_philo				*philo;
	int					i;
}	t_args;

unsigned long long	gettime(void);
void				ft_usleep(unsigned long long time);
int					ft_strlen(char *str);
void				ft_error(char *str);
int					ft_atoi(char *str);
void				take_forks(t_philo *philo);
int					parsing(int argc, char **argv, t_args *arg);
void				sleeping_and_thinking(t_philo *philo);
void				eating(t_philo *philo);
void				*life(void *ptr);
int					love_of_thanos(t_args *args, int *i, int *opt_arg);
void				take_forks_again(t_philo *philo);
void				philo_init(int argc, t_args *arg);

#endif
