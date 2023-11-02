/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idryab <idryab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:23:08 by idryab            #+#    #+#             */
/*   Updated: 2023/05/30 02:16:34 by idryab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timestamp(void)

{
	struct timeval	t;
	long long		time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return ((int)time);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	r;
	int		s;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + s * (str[i] - '0');
		i++;
		if (r > INT_MAX)
			return (-1);
		if (r < INT_MIN)
			return (0);
	}
	return ((int)r);
}

void	mf_usleep(int time)
{
	int	x;

	x = timestamp();
	while (timestamp() - x < time)
		usleep(10);
}
