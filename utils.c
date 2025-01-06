/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:17:26 by nsauret           #+#    #+#             */
/*   Updated: 2025/01/06 18:26:32 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long milliseconds, t_infos *infos)
{
	long	start;

	start = get_time();
	pthread_mutex_lock(&infos->mutex_someone_died);
	while ((get_time() - start) < milliseconds && !infos->someone_died)
	{
		pthread_mutex_unlock(&infos->mutex_someone_died);
		usleep(500);
		pthread_mutex_lock(&infos->mutex_someone_died);
	}
	pthread_mutex_unlock(&infos->mutex_someone_died);
}

int	everyone_finished(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->infos->number_of_philosophers)
	{
		if (!philo->finished)
			return (0);
		i++;
		philo = philo->next;
	}
	return (1);
}

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	display_message(t_philosopher *philo, int status)
{
	long	time;

	pthread_mutex_lock(&philo->infos->write_mutex);
	time = get_time() - philo->infos->time_start;
	if (status == 4)
		printf(BOLD_RED"%ld %d died\n"RESET, time, philo->number);
	pthread_mutex_lock(&philo->infos->mutex_someone_died);
	if (philo->infos->someone_died)
	{
		pthread_mutex_unlock(&philo->infos->mutex_someone_died);
		pthread_mutex_unlock(&philo->infos->write_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->infos->mutex_someone_died);
	if (status == 0)
		printf("%ld %d has taken a fork\n"RESET, time, philo->number);
	else if (status == 1)
		printf(PURPLE"%ld %d is eating\n"RESET, time, philo->number);
	else if (status == 2)
		printf(BLUE"%ld %d is sleeping\n"RESET, time, philo->number);
	else if (status == 3)
		printf(GREEN"%ld %d is thinking\n"RESET, time, philo->number);
	pthread_mutex_unlock(&philo->infos->write_mutex);
}
