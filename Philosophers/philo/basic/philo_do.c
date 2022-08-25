/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhizdahr <zhizdahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:56:40 by zhizdahr          #+#    #+#             */
/*   Updated: 2022/06/26 15:50:59 by zhizdahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../philosophers.h"

void	ft_usleep(long long time)
{
	long long	start;

	start = get_timestamp();
	while (get_timestamp() - start < time)
		usleep(100);
}

int	philo_eating(t_table *table, t_philo *philo)
{
	if (table->flag_of_death)
		return (1);
	pthread_mutex_lock(&table->fork[philo->left_fork]);
	philo_print(table, philo, "has taken a fork");
	pthread_mutex_lock(&philo->door);
	if (table->count_philo == 1)
	{
		pthread_mutex_unlock(&philo->door);
		return (pthread_mutex_unlock(&table->fork[table->philo->left_fork]), 1);
	}
	pthread_mutex_lock(&table->fork[philo->right_fork]);
	philo_print(table, philo, "has taken a fork");
	philo->last_eat = get_timestamp();
	philo_print(table, philo, "is eating");
	philo->count_eat++;
	pthread_mutex_unlock(&philo->door);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&table->fork[philo->left_fork]);
	pthread_mutex_unlock(&table->fork[philo->right_fork]);
	return (0);
}

void	philo_sleeping(t_table *table, t_philo *philo)
{
	if (table->flag_of_death)
		return ;
	philo_print(table, philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	philo_thinking(t_table *table, t_philo *philo)
{
	if (table->flag_of_death)
		return ;
	philo_print(table, philo, "is thinking");
}
