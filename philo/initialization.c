/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idryab <idryab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:22:23 by idryab            #+#    #+#             */
/*   Updated: 2023/06/14 07:55:35 by idryab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initilize_mutexes(pthread_mutex_t	**fork,
	pthread_mutex_t	**ml_mutex, t_codata *data)
{
	int	i;

	i = 0;
	(*fork) = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if ((*fork) == NULL)
		return ;
	while (i < data->philo_nb)
		pthread_mutex_init(&(*fork)[i++], NULL);
	i = 0;
	(*ml_mutex) = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if ((*ml_mutex) == NULL)
		return ;
	while (i < data->philo_nb)
		pthread_mutex_init(&(*ml_mutex)[i++], NULL);
}

static int	initialize_philo(t_philo **philo, t_codata *data)
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*ml_mutex;
	int				i;

	initilize_mutexes(&fork, &ml_mutex, data);
	i = 0;
	while (i < data->philo_nb)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].lfork = i;
		(*philo)[i].rfork = (i + 1) % data->philo_nb;
		(*philo)[i].fork = fork;
		(*philo)[i].id_ml_mutex = i;
		(*philo)[i].ml_mutex = ml_mutex;
		(*philo)[i].data = data;
		(*philo)[i].meals_count = 0;
		(*philo)[i].last_meal = timestamp();
		(*philo)[i].start_time = timestamp();
		i++;
	}
	return (1);
}

static void	initialize_codata(t_codata *data, char **av, int ac)
{
	data->philo_nb = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_slp = ft_atoi(av[4]);
	data->is_dead = 0;
	data->is_all_ate_all = 0;
	data->must_eat = -1;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
}

t_philo	*initialization(t_codata *data, char **av, int ac)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data->philo_nb);
	if (philo == NULL)
		return (NULL);
	initialize_codata(data, av, ac);
	initialize_philo(&philo, data);
	return (philo);
}
