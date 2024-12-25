/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:17:26 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/25 17:10:56 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	if (status == 0)
		printf("%ld %d has taken a fork\n", time, philo->number);
	else if (status == 1)
		printf("%ld %d is eating\n", time, philo->number);
	else if (status == 2)
		printf("%ld %d is sleeping\n", time, philo->number);
	else if (status == 3)
		printf("%ld %d is thinking\n", time, philo->number);
	else
		printf("%ld %d died\n", time, philo->number);
	pthread_mutex_unlock(&philo->infos->write_mutex);
}
