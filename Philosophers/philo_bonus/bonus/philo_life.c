/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhizdahr <zhizdahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:53:54 by zhizdahr          #+#    #+#             */
/*   Updated: 2022/06/26 15:14:26 by zhizdahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../philosophers.h"

long long	get_timestamp(void)
{
	struct timeval	t;
	long long		now;

	gettimeofday (&t, NULL);
	now = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	return (now);
}

int	start_game(t_philo *philo)
{
	pthread_create(&philo->track_death, NULL, &death_is_near, philo);
	if (philo->name % 2 == 1)
		usleep(500);
	while (1)
	{
		if (philo->count_of_lunch)
			if (philo->count_eat == philo->count_of_lunch)
				break ;
		if (philo_do(philo))
			break ;
	}
	if (pthread_join(philo->track_death, NULL))
		return (ft_error(philo));
	return (0);
}

void	*death_is_near(void *tmp)
{
	t_philo		*p;

	p = tmp;
	while (1)
	{
		if (p->count_of_lunch)
			if (p->count_eat == p->count_of_lunch)
				break ;
		if (get_timestamp() - p->time_last_eat > p->time_to_die)
		{
			p->flag_of_death = 1;
			sem_wait(p->sem_print);
			printf("%lld %d is died\n",
				get_timestamp() - p->time_start, p->name);
			break ;
		}
	}
	if (p->flag_of_death)
		exit (1);
	else
		exit (0);
}

int	killer(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->count_philo)
		kill(philo->pid[i], SIGKILL);
	return (0);
}

int	philo_life(t_philo *all)
{
	int	i;
	int	status;

	i = -1;
	all->time_start = get_timestamp();
	while (++i < all->count_philo)
	{
		all->pid[i] = fork();
		if (all->pid[i] == -1)
			return (ft_error(all));
		if (all->pid[i] == 0)
		{
			all->name = i + 1;
			all->time_last_eat = all->time_start;
			if (start_game(all))
				return (0);
		}
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WEXITSTATUS(status) == 1)
			return (killer(all));
	}
	return (0);
}
