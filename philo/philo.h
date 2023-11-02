/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idryab <idryab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:22:35 by idryab            #+#    #+#             */
/*   Updated: 2023/06/14 07:55:38 by idryab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_data
{
	int					philo_nb;
	int					time_die;
	int					time_eat;
	int					time_slp;
	int					time_thk;
	int					must_eat;
	int					is_all_ate_all;
	int					is_dead;
	pthread_mutex_t		pprint;
	pthread_mutex_t		ml_count_mutext;
}	t_codata;

typedef struct s_philo
{
	int					id;
	int					meals_count;
	int					last_meal;
	int					start_time;
	int					lfork;
	int					rfork;
	pthread_mutex_t		*fork;
	int					id_ml_mutex;
	pthread_mutex_t		*ml_mutex;
	t_codata			*data;
}	t_philo;

int			ft_atoi(const char *str);
t_philo		*initialization(t_codata *data, char **av, int ac);
void		create_threads(t_philo *philo);
void		prevent_print(t_philo *philo, char *str);
int			timestamp(void);
void		mf_usleep(int time);

#endif
