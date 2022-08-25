/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhizdahr <zhizdahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:53:44 by zhizdahr          #+#    #+#             */
/*   Updated: 2022/06/26 11:53:45 by zhizdahr         ###   ########.fr       */
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

int	philo_do(t_philo *philo)
{
	sem_wait(philo->sem_fork);
	philo_print(philo, "has taken a fork");
	if (philo->count_philo == 1)
		return (sem_post(philo->sem_fork), 1);
	sem_wait(philo->sem_fork);
	philo_print(philo, "has taken a fork");
	philo_print(philo, "is eating");
	philo->time_last_eat = get_timestamp();
	ft_usleep(philo->time_to_eat);
	sem_post(philo->sem_fork);
	sem_post(philo->sem_fork);
	philo->count_eat++;
	philo_print(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	philo_print(philo, "is thinking");
	return (0);
}
