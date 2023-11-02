/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_proccess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idryab <idryab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 02:57:24 by idryab            #+#    #+#             */
/*   Updated: 2023/06/10 10:49:04 by idryab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	prevent_print(t_philo *philo, char *str)
{
	sem_wait(philo->data->pprint);
	printf(str, timestamp() - philo->start_time, philo->id);
	sem_post(philo->data->pprint);
}

void	*is_dead(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->sem2);
		if (timestamp() - philo->last_meal >= philo->data->time_die)
		{
			sem_wait(philo->data->pprint);
			printf("%d %d is dead\n",
				timestamp() - philo->start_time, philo->id);
			kill(0, SIGINT);
			break ;
		}
		sem_post(philo->data->sem2);
		usleep(100);
	}
	return (NULL);
}

static void	*routing_function(t_philo *philo)
{
	pthread_t	tdeath;

	pthread_create(&tdeath, NULL, &is_dead, philo);
	pthread_detach(tdeath);
	while (1)
	{
		sem_wait(philo->data->sem1);
		prevent_print(philo, "%d %d has taken a fork\n");
		sem_wait(philo->data->sem1);
		prevent_print(philo, "%d %d has taken a fork\n");
		prevent_print(philo, "%d %d is eating\n");
		philo->last_meal = timestamp();
		philo->meals_count += 1;
		mf_usleep(philo->data->time_eat);
		sem_post(philo->data->sem1);
		sem_post(philo->data->sem1);
		prevent_print(philo, "%d %d is sleeping\n");
		mf_usleep(philo->data->time_slp);
		prevent_print(philo, "%d %d is thinking\n");
		if (philo->data->must_eat != -1
			&& philo->meals_count >= philo->data->must_eat)
			exit(0);
	}
	return (NULL);
}

void	run_proccess(t_philo *philo, t_codata *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			routing_function(&philo[i]);
		i++;
	}
}
