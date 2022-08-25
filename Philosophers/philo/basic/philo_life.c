/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhizdahr <zhizdahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:56:45 by zhizdahr          #+#    #+#             */
/*   Updated: 2022/06/26 15:50:18 by zhizdahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../philosophers.h"

void	philo_print(t_table	*table, t_philo *philo, char *str)
{
	if (table->flag_of_death)
		return ;
	pthread_mutex_lock(&table->print);
	if (table->flag_of_death)
		return ;
	printf("%lld %d %s\n",
		get_timestamp() - philo->time_start, philo->id, str);
	pthread_mutex_unlock(&table->print);
}

long long	get_timestamp(void)
{
	struct timeval	t;
	long long		now;

	gettimeofday (&t, NULL);
	now = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	return (now);
}

void	*start_game(void *tmp)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)tmp;
	table = philo->arg;
	if (philo->id % 2 == 0)
	{
		philo_print(table, philo, "is thinking");
		usleep(50);
	}
	while (!table->flag_of_death)
	{
		if (table->count_of_lunch)
		{
			if (philo->count_eat > table->count_of_lunch)
			{
				return (NULL);
			}
		}
		if (philo_eating(table, philo))
			return (NULL);
		philo_sleeping(table, philo);
		philo_thinking(table, philo);
	}
	return (NULL);
}

void	*death_is_near(void *tmp)
{
	t_table		*all;
	t_philo		*p;
	int			i;

	all = tmp;
	p = all->philo;
	while (1)
	{
		i = -1;
		while (++i < all->count_philo)
		{
			pthread_mutex_lock(&p->door);
			if (all->count_of_lunch && p->count_eat > all->count_of_lunch)
				return (pthread_mutex_unlock(&p->door), NULL);
			pthread_mutex_unlock(&p->door);
			if (get_timestamp() - p[i].last_eat > p[i].time_to_die)
			{
				all->flag_of_death = 1;
				pthread_mutex_lock(&all->print);
				return (printf("%lld %d is died\n",
						get_timestamp() - p->time_start, p->id), NULL);
			}
		}
	}
	return (NULL);
}

int	philo_life(t_table *all)
{
	int			i;
	pthread_t	check;

	i = -1;
	all->time_start = get_timestamp();
	while (++i < all->count_philo)
	{
		all->philo[i].time_start = all->time_start;
		all->philo[i].last_eat = all->time_start;
	}
	i = -1;
	while (++i < all->count_philo)
		pthread_create(&all->thread[i], NULL, &start_game, &all->philo[i]);
	pthread_create(&check, NULL, &death_is_near, all);
	pthread_mutex_unlock(&all->print);
	pthread_join(check, NULL);
	i = -1;
	while (++i < all->count_philo)
		pthread_join(all->thread[i], NULL);
	return (0);
}
