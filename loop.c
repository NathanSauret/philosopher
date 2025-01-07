/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:58:19 by nsauret           #+#    #+#             */
/*   Updated: 2025/01/07 16:34:51 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_and_exit(t_data *data, int number_to_join)
{
	int	i;

	pthread_mutex_lock(&data->infos->mutex_someone_died);
	data->infos->someone_died = 1;
	pthread_mutex_unlock(&data->infos->mutex_someone_died);
	pthread_mutex_lock(&data->infos->mutex_start_signal);
	data->infos->start_signal = 1;
	pthread_mutex_unlock(&data->infos->mutex_start_signal);
	data->philo = get_philosopher(data, 1);
	i = 0;
	while (i < number_to_join)
	{
		pthread_join(data->philo->thread, NULL);
		printf("jkjdksjdksdjksdsd\n");
		data->philo = data->philo->next;
		i++;
	}
	data->philo = get_philosopher(data, 1);
}

static int	routine(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i++ != philo->infos->nbr_must_eat)
	{
		if (!safe_take_fork(philo, philo->fork_at_left))
			return (0);
		if (!safe_take_fork(philo, &philo->fork_at_right))
			return (0);
		if (!safe_eating(philo))
			return (0);
		if (!safe_put_down_fork(philo, philo->fork_at_left))
			return (0);
		if (!safe_put_down_fork(philo, &philo->fork_at_right))
			return (0);
		if (!safe_sleeping(philo))
			return (0);
		if (!safe_thinking(philo))
			return (0);
	}
	return (1);
}

static void	*philosopher_loop(void *void_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) void_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->infos->mutex_start_signal);
		if (philo->infos->start_signal)
		{
			pthread_mutex_unlock(&philo->infos->mutex_start_signal);
			break ;
		}
		pthread_mutex_unlock(&philo->infos->mutex_start_signal);
	}
	if (philo->number % 2 == 0)
		ft_usleep(2, philo->infos);
	if (!routine(philo))
		return (NULL);
	philo->finished = 1;
	display_message(philo, FINISHED_MSG);
	return (NULL);
}

void	loop(t_data	*data)
{
	t_philosopher	*tmp;
	int				i;

	tmp = data->philo;
	i = 0;
	while (i < data->infos->number_of_philosophers)
	{
		if (pthread_create(&tmp->thread, NULL, philosopher_loop, tmp) != 0)
			return (join_and_exit(data, i), (void) NULL);
		tmp = tmp->next;
		i++;
	}
	if (pthread_create(&data->abyss_watcher, NULL, abyss_watcher_loop, tmp))
		return (join_and_exit(data, i), (void) NULL);
	pthread_mutex_lock(&data->infos->mutex_start_signal);
	data->infos->start_signal = 1;
	pthread_mutex_unlock(&data->infos->mutex_start_signal);
	i = 0;
	while (i < data->infos->number_of_philosophers)
	{
		pthread_join(data->philo->thread, NULL);
		data->philo = data->philo->next;
		i++;
	}
	pthread_join(data->abyss_watcher, NULL);
}
