/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhizdahr <zhizdahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:56:24 by zhizdahr          #+#    #+#             */
/*   Updated: 2022/06/26 15:31:51 by zhizdahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../philosophers.h"

void	init(t_table *data, int ac, char **av)
{
	data->count_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->count_of_lunch = 0;
	if (ac == 6)
		data->count_of_lunch = ft_atoi(av[5]);
	data->flag_of_death = 0;
	data->time_start = 0;
	pthread_mutex_init(&data->print, NULL);
	data->thread = NULL;
	data->philo = NULL;
	data->fork = NULL;
}

int	init_philo(t_table *all)
{
	int	i;

	i = 0;
	while (i < all->count_philo)
	{
		all->philo[i].id = i + 1;
		all->philo[i].time_to_die = all->time_to_die;
		all->philo[i].time_to_eat = all->time_to_eat;
		all->philo[i].time_to_sleep = all->time_to_sleep;
		all->philo[i].count_eat = 0;
		all->philo[i].left_fork = i;
		if (i < all->count_philo - 1)
			all->philo[i].right_fork = i + 1;
		else
			all->philo[i].right_fork = 0;
		all->philo[i].last_eat = 0;
		all->philo[i].arg = all;
		i++;
	}
	return (0);
}

int	init_mutex(t_table *all)
{
	int	i;

	i = 0;
	while (i < all->count_philo)
	{
		if (pthread_mutex_init(&all->fork[i], NULL))
			return (1);
		if (pthread_mutex_init(&all->philo[i++].door, NULL))
			return (1);
	}
	return (0);
}
