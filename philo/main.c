/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idryab <idryab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:22:28 by idryab            #+#    #+#             */
/*   Updated: 2023/05/30 02:01:10 by idryab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_numeric(char const *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

static int	ft_check_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (0);
	if ((ac == 6 && ft_atoi(av[5]) == 0))
		return (0);
	if (ft_atoi(av[1]) == 0)
		return (0);
	while (ac-- > 1)
	{
		if (ft_is_numeric (av[ac]) == 0)
			return (0);
		if (ft_atoi(av[ac]) < 0)
			return (0);
	}
	return (1);
}

static int	meal_mutex(t_philo *philo, t_codata *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_lock(&philo->ml_mutex[philo[i].id_ml_mutex]);
		if (philo[i].meals_count < data->must_eat)
			return (pthread_mutex_unlock
				(&philo->ml_mutex[philo[i].id_ml_mutex]), 0);
		pthread_mutex_unlock(&philo->ml_mutex[philo[i].id_ml_mutex]);
		i++;
	}
	return (1);
}

static void	f(t_philo *philo)
{
	free(philo->fork);
	free(philo->ml_mutex);
}

int	main(int ac, char **av)
{
	t_codata	data;
	t_philo		*philo;
	int			i;

	philo = NULL;
	if (ft_check_args(ac, av) == 0)
		return (printf("somthing went wrong... try to fix it.\n"), 0);
	philo = initialization(&data, av, ac);
	create_threads(philo);
	i = 0;
	while (1)
	{
		if (i == data.philo_nb)
			i = 0;
		pthread_mutex_lock(&philo->ml_mutex[philo[i].id_ml_mutex]);
		if (timestamp() - philo[i].last_meal >= data.time_die)
		{
			return (data.is_dead = 1, printf("%d %d is dead\n"
					, timestamp() - philo->start_time, philo->id), f(philo), 0);
		}
		pthread_mutex_unlock(&philo->ml_mutex[philo[i].id_ml_mutex]);
		if (data.must_eat > 0 && meal_mutex(philo, &data) == 1)
			return (f(philo), 0);
		i++;
	}
}
