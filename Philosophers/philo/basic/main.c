/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhizdahr <zhizdahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:56:35 by zhizdahr          #+#    #+#             */
/*   Updated: 2022/06/26 15:32:06 by zhizdahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../philosophers.h"

int	check_arg(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments.\n");
		exit (1);
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0
		|| (ac == 6 && ft_atoi(av[5]) <= 0))
	{
		printf("Error: Wrong arguments.\n");
		exit (1);
	}
	return (0);
}

int	malloc_time(t_table *all)
{
	all->philo = malloc(sizeof(t_philo) * all->count_philo);
	if (!all->philo)
		return (1);
	all->fork = malloc(sizeof(pthread_mutex_t) * all->count_philo);
	if (!all->fork)
		return (1);
	all->thread = malloc(sizeof(pthread_t) * all->count_philo);
	if (!all->thread)
		return (1);
	return (0);
}

void	fullfree(t_table *all)
{
	free(all->philo);
	free(all->fork);
	free(all->thread);
}

int	main(int argc, char **argv)
{
	t_table	data;

	check_arg(argc, argv);
	init(&data, argc, argv);
	malloc_time(&data);
	init_philo(&data);
	init_mutex(&data);
	philo_life(&data);
	fullfree(&data);
	return (0);
}
