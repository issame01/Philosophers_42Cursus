/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strange_things.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idryab <idryab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:22:41 by idryab            #+#    #+#             */
/*   Updated: 2023/06/14 08:02:59 by idryab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	prevent_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->pprint);
	if (philo->data->is_dead == 0)
	{
		printf(str, timestamp() - philo->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->data->pprint);
}

void	est(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork[philo->lfork]);
	prevent_print(philo, "%llu %d has taken a fork\n");
	pthread_mutex_lock(&philo->fork[philo->rfork]);
	prevent_print(philo, "%llu %d has taken a fork\n");
	prevent_print(philo, "%llu %d is eating\n");
	pthread_mutex_lock(&philo->ml_mutex[philo->id_ml_mutex]);
	philo->last_meal = timestamp();
	philo->meals_count += 1;
	pthread_mutex_unlock(&philo->ml_mutex[philo->id_ml_mutex]);
	mf_usleep(philo->data->time_eat);
	pthread_mutex_unlock(&philo->fork[philo->rfork]);
	pthread_mutex_unlock(&philo->fork[philo->lfork]);
	prevent_print(philo, "%llu %d is sleeping\n");
	mf_usleep(philo->data->time_slp);
	prevent_print(philo, "%llu %d is thinking\n");
}

static void	*routing_function(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(200);
	while (philo->data->is_dead == 0)
	{
		if (philo->data->philo_nb > 1)
			est(philo);
		else
		{
			pthread_mutex_lock(&philo->fork[philo->lfork]);
			prevent_print(philo, "%llu %d has taken a fork\n");
		}
	}
	return (NULL);
}

void	create_threads(t_philo *philo)
{
	int			i;
	pthread_t	*threadd;

	threadd = malloc(sizeof(threadd) * philo->data->philo_nb);
	if (!threadd)
		return ;
	i = 0;
	while (i < philo->data->philo_nb)
	{
		pthread_create(&threadd[i], NULL, &routing_function, &philo[i]);
		pthread_detach(threadd[i]);
		i++;
	}
	free(threadd);
}
