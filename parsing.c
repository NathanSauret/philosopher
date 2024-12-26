/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:27:33 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/26 15:53:57 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atoi(const char *nptr)
{
	long long		res;

	res = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		return (-1);
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	res = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = 10 * res + (*nptr++ - '0');
		if (res > 2147483647)
			return (-1);
	}
	if (!res)
		return (-1);
	return (res);
}

int	parsing(t_infos *infos, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf("Error: Wrong number of arguments\n"), 0);
	infos->number_of_philosophers = ft_atoi(argv[1]);
	if (infos->number_of_philosophers == -1)
		return (printf("Error: Wrong argument\n"), 0);
	infos->time_to_die = ft_atoi(argv[2]);
	if (infos->time_to_die == -1)
		return (printf("Error: Wrong argument\n"), 0);
	infos->time_to_eat = ft_atoi(argv[3]);
	if (infos->time_to_eat == -1)
		return (printf("Error: Wrong argument\n"), 0);
	infos->time_to_sleep = ft_atoi(argv[4]);
	if (infos->time_to_sleep == -1)
		return (printf("Error: Wrong argument\n"), 0);
	if (argc == 6)
	{
		infos->nbr_must_eat = ft_atoi(argv[5]);
		if (infos->nbr_must_eat == -1)
			return (printf("Error: Wrong argument\n"), 0);
	}
	else
		infos->nbr_must_eat = -1;
	infos->someone_died = 0;
	infos->start_signal = 0;
	return (pthread_mutex_init(&infos->write_mutex, NULL), 1);
}
