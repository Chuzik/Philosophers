/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhizdahr <zhizdahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 18:19:38 by zhizdahr          #+#    #+#             */
/*   Updated: 2022/06/26 12:00:59 by zhizdahr         ###   ########.fr       */
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
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int			count_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			count_of_lunch;
	int			name;
	int			count_eat;
	int			flag_of_death;
	long long	time_start;
	long long	time_last_eat;
	pid_t		*pid;
	pthread_t	track_death;
	sem_t		*sem_print;
	sem_t		*sem_fork;
}		t_philo;

long long	ft_atoi(const char *str);
int			philo_life(t_philo *all);
int			start_game(t_philo *philo);
void		*death_is_near(void *tmp);
long long	get_timestamp(void);
int			philo_do(t_philo *philo);
int			init_philo(t_philo *data, int ac, char **av);
void		ft_usleep(long long time);
void		philo_print(t_philo *philo, char *str);
int			killer(t_philo *philo);
int			ft_error(t_philo *all);
void		fullfree(t_philo *philo);
int			sem_init_philo(t_philo *data);

#endif