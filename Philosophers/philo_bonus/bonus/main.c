/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhizdahr <zhizdahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:52:43 by zhizdahr          #+#    #+#             */
/*   Updated: 2022/06/26 12:00:40 by zhizdahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../philosophers.h"

void	philo_print(t_philo *philo, char *str)
{
	sem_wait(philo->sem_print);
	printf("%lld %d %s\n",
		get_timestamp() - philo->time_start, philo->name, str);
	sem_post(philo->sem_print);
}

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

void	fullfree(t_philo *philo)
{
	sem_unlink("print");
	sem_unlink("fork");
	sem_close(philo->sem_print);
	sem_close(philo->sem_fork);
	free(philo->pid);
}

int	main(int argc, char **argv)
{
	t_philo	data;

	check_arg(argc, argv);
	init_philo(&data, argc, argv);
	if (sem_init_philo(&data))
		return (1);
	philo_life(&data);
	fullfree(&data);
	return (0);
}
