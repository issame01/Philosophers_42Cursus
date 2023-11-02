/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idryab <idryab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:22:35 by idryab            #+#    #+#             */
/*   Updated: 2023/06/14 07:58:08 by idryab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_data
{
	int					philo_nb;
	int					time_die;
	int					time_eat;
	int					time_slp;
	int					must_eat;
	int					is_dead;
	sem_t				*sem1;
	sem_t				*sem2;
	sem_t				*pprint;
}	t_codata;

typedef struct s_philo
{
	int					id;
	int					pid;
	int					meals_count;
	int					last_meal;
	int					start_time;
	t_codata			*data;
}	t_philo;

int			ft_atoi(const char *str);
t_philo		*initialization(t_codata *data, char **av, int ac);
void		run_proccess(t_philo *philo, t_codata *data);
int			timestamp(void);
void		mf_usleep(int time);

#endif
