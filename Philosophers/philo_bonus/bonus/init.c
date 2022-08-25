/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhizdahr <zhizdahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:52:28 by zhizdahr          #+#    #+#             */
/*   Updated: 2022/06/26 15:07:25 by zhizdahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../philosophers.h"

int	ft_error(t_philo *all)
{
	printf("Error");
	fullfree(all);
	return (1);
}

int	init_philo(t_philo *data, int ac, char **av)
{
	data->count_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->count_of_lunch = 0;
	if (ac == 6)
		data->count_of_lunch = ft_atoi(av[5]);
	data->flag_of_death = 0;
	data->name = 0;
	data->count_eat = 0;
	data->time_start = 0;
	data->time_last_eat = 0;
	return (0);
}

int	sem_init_philo(t_philo *data)
{
	sem_unlink("print");
	sem_unlink("fork");
	data->sem_print = sem_open("print", O_CREAT, 0644, 1);
	if (data->sem_print == SEM_FAILED)
		return (ft_error(data));
	data->sem_fork = sem_open("fork", O_CREAT, 0644, data->count_philo);
	if (data->sem_fork == SEM_FAILED)
		return (ft_error(data));
	data->pid = malloc(sizeof(pid_t) * data->count_philo);
	if (!data->pid)
	{
		sem_close(data->sem_print);
		sem_close(data->sem_fork);
		return (ft_error(data));
	}
	return (0);
}
