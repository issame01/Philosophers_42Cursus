/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idryab <idryab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:22:28 by idryab            #+#    #+#             */
/*   Updated: 2023/06/14 07:57:56 by idryab           ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_codata	data;
	t_philo		*philo;
	int			i;

	philo = NULL;
	if (ft_check_args(ac, av) == 0)
		return (printf("somthing went wrong... try to fix it.\n"), 0);
	philo = initialization(&data, av, ac);
	run_proccess(philo, &data);
	i = 0;
	while (i < data.philo_nb)
	{
		waitpid(philo[i].pid, NULL, 0);
		i++;
	}
	return (0);
}
