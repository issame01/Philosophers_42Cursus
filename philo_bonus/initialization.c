/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idryab <idryab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:22:23 by idryab            #+#    #+#             */
/*   Updated: 2023/06/10 10:46:05 by idryab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*initialize_philo(t_codata *data)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * data->philo_nb);
	if (philo == NULL)
		return (NULL);
	i = 0;
	while (i < data->philo_nb)
	{
		philo[i].id = i + 1;
		philo[i].pid = -1;
		philo[i].data = data;
		philo[i].meals_count = 0;
		philo[i].last_meal = timestamp();
		philo[i].start_time = timestamp();
		i++;
	}
	return (philo);
}

static void	initialize_codata(t_codata *data, char **av, int ac)
{
	data->philo_nb = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_slp = ft_atoi(av[4]);
	data->is_dead = 0;
	data->must_eat = -1;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
}

static void	initialize_sema(t_codata **data)
{
	sem_unlink("/sem1");
	sem_unlink("/pprint");
	sem_unlink("/sem2");
	(*data)->sem1 = sem_open("/sem1", O_CREAT, 0644, (*data)->philo_nb);
	(*data)->pprint = sem_open("/pprint", O_CREAT, 0644, 1);
	(*data)->sem2 = sem_open("/sem2", O_CREAT, 0644, 1);
}

t_philo	*initialization(t_codata *data, char **av, int ac)
{
	t_philo	*philo;

	initialize_codata(data, av, ac);
	initialize_sema(&data);
	philo = initialize_philo(data);
	return (philo);
}
