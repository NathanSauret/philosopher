/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:58:19 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/26 15:21:52 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (!philo->infos->start_signal)
		continue ;
	if (philo->number % 2 == 0)
		ft_usleep(1, philo->infos);
	if (!routine(philo))
		return (NULL);
	return (philo->finished = 1, NULL);
}

void	loop(t_data	*data)
{
	t_philosopher	*tmp_philo;
	int				i;

	tmp_philo = data->philo;
	i = 0;
	while (i < data->infos->number_of_philosophers)
	{
		pthread_create(&tmp_philo->thread, NULL, philosopher_loop, tmp_philo);
		tmp_philo = tmp_philo->next;
		i++;
	}
	pthread_create(&data->abyss_watcher, NULL, abyss_watcher_loop, tmp_philo);
	tmp_philo->infos->start_signal = 1;
	i = 0;
	while (i < data->infos->number_of_philosophers)
	{
		pthread_join(data->philo->thread, NULL);
		data->philo = data->philo->next;
		i++;
	}
	pthread_join(data->abyss_watcher, NULL);
}
