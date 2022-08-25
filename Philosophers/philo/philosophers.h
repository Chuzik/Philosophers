/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhizdahr <zhizdahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 18:19:38 by zhizdahr          #+#    #+#             */
/*   Updated: 2022/06/26 15:32:27 by zhizdahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_eat;
	int				left_fork;
	int				right_fork;
	long long		time_start;
	long long		last_eat;
	pthread_mutex_t	door;
	struct s_table	*arg;
}		t_philo;

typedef struct s_table
{
	int				count_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_of_lunch;
	int				flag_of_death;
	long long		time_start;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	t_philo			*philo;
}		t_table;

long long	ft_atoi(const char *str);
int			philo_life(t_table *all);
void		*start_game(void *tmp);
void		*death_is_near(void *tmp);
long long	get_timestamp(void);
int			philo_eating(t_table *table, t_philo *philo);
void		philo_sleeping(t_table *table, t_philo *philo);
void		philo_thinking(t_table *table, t_philo *philo);
void		philo_print(t_table	*table, t_philo *philo, char *str);
void		init(t_table *data, int ac, char **av);
int			init_philo(t_table *all);
void		ft_usleep(long long time);
int			init_mutex(t_table *all);

#endif