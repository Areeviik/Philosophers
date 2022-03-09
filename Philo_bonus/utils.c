/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:19:13 by akhachat          #+#    #+#             */
/*   Updated: 2022/02/14 19:08:51 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(0);
}

int	ft_atoi(char *str)
{
	int		i;
	int		min;
	long	num;

	i = 0;
	num = 0;
	min = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			min = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		num = num * 10;
		num = num + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		ft_error("Error\nNon numeric argument\n");
	return (num * min);
}

void	message(t_philo *philo, char *str)
{
	long	time;

	time = gettime() - philo->first_time;
	printf("%ld: Philosopher %d %s\n", time, philo->name, str);
}
