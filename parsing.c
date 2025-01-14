/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:27:33 by nsauret           #+#    #+#             */
/*   Updated: 2025/01/14 15:08:22 by nsauret          ###   ########.fr       */
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

static int	error_handler(t_infos *infos, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf(BOLD_RED"Error: Wrong number of arguments\n"RESET), 0);
	infos->number_of_philosophers = ft_atoi(argv[1]);
	if (infos->number_of_philosophers == -1)
		return (printf(BOLD_RED"Error: Wrong argument\n"RESET), 0);
	infos->time_to_die = ft_atoi(argv[2]);
	if (infos->time_to_die == -1)
		return (printf(BOLD_RED"Error: Wrong argument\n"RESET), 0);
	infos->time_to_eat = ft_atoi(argv[3]);
	if (infos->time_to_eat == -1)
		return (printf(BOLD_RED"Error: Wrong argument\n"RESET), 0);
	infos->time_to_sleep = ft_atoi(argv[4]);
	if (infos->time_to_sleep == -1)
		return (printf(BOLD_RED"Error: Wrong argument\n"RESET), 0);
	if (argc == 6)
	{
		infos->nbr_must_eat = ft_atoi(argv[5]);
		if (infos->nbr_must_eat == -1)
			return (printf(BOLD_RED"Error: Wrong argument\n"RESET), 0);
	}
	else
		infos->nbr_must_eat = -1;
	return (1);
}

int	parsing(t_infos *infos, int argc, char **argv)
{
	if (!error_handler(infos, argc, argv))
		return (0);
	if (pthread_mutex_init(&infos->mutex_someone_died, NULL) != 0)
		return (print_error(MUTEX_ERROR), 0);
	infos->someone_died = 0;
	if (pthread_mutex_init(&infos->mutex_start_signal, NULL) != 0)
	{
		pthread_mutex_destroy(&infos->mutex_someone_died);
		return (print_error(MUTEX_ERROR), 0);
	}
	infos->start_signal = 0;
	if (pthread_mutex_init(&infos->write_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&infos->mutex_someone_died);
		pthread_mutex_destroy(&infos->mutex_start_signal);
		return (print_error(MUTEX_ERROR), 0);
	}
	return (1);
}
