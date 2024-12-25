/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:36:38 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/25 18:05:43 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	everyone_finished(t_philosopher *philo)
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
static void	*abyss_watcher_loop(void *void_data)
{
	t_data			*data;
	t_philosopher	*philo;

	data = (t_data *) void_data;
	philo = data->philo;
	while (!everyone_finished(philo))
	{
		if (get_time() - philo->last_eat_time > philo->infos->time_to_die)
		{
			display_message(philo, DEAD_MSG);
			// free_everything(data);
			exit (1);
			return (NULL);
		}
		philo = philo->next;
	}
	return (NULL);
}

static void	*philosopher_loop(void *void_philo)
{
	t_philosopher	*philo;
	int				i;

	philo = (t_philosopher *) void_philo;
	// if (philo->number % 2 == 0)
	// 	usleep(10);
	i = 0;
	while (i != philo->infos->nbr_must_eat)
	{
		pthread_mutex_lock(philo->fork_at_left);
		philo->hold_left_hand = 1;
		display_message(philo, FORK_TAKEN_MSG);

		pthread_mutex_lock(&philo->fork_at_right);
		philo->hold_right_hand = 1;
		display_message(philo, FORK_TAKEN_MSG);

		display_message(philo, EATING_MSG);
		usleep(philo->infos->time_to_eat);
		philo->last_eat_time = get_time();

		pthread_mutex_unlock(philo->fork_at_left);
		philo->hold_left_hand = 0;

		pthread_mutex_unlock(&philo->fork_at_right);
		philo->hold_right_hand = 0;

		display_message(philo, SLEEPING_MSG);
		usleep(philo->infos->time_to_sleep);

		display_message(philo, THINKING_MSG);
		usleep(100);
		i++;
	}
	return (philo->finished = 1, NULL);
}

int	main(int argc, char *argv[])
{
	t_data			data;
	t_infos			infos;
	t_philosopher	*tmp_philo;
	int				i;

	if (!parsing(&data, &infos, argc, argv))
		return (1);
	if (!create_philosopers(&data, &infos))
		return (free_everything(&data), 1);
	// printf("time start: %ld\n", data.philo->infos->time_start);
	// printf("time passed from start: %ld\n", get_time() - data.philo->infos->time_start);
	// printf("number of philosophers: %d\n", data.philo->infos->number_of_philosophers);
	// printf("time to die: %ld\n", data.philo->infos->time_to_die);
	// printf("time to eat: %ld\n", data.philo->infos->time_to_eat);
	// printf("time to sleep: %ld\n", data.philo->infos->time_to_sleep);
	// printf("number of time each philosopher must eat: %d\n", data.philo->infos->nbr_must_eat);
	// return (1);
	tmp_philo = data.philo;
	i = 0;
	while (i < infos.number_of_philosophers)
	{
		pthread_create(&tmp_philo->thread, NULL, philosopher_loop, tmp_philo);
		tmp_philo = tmp_philo->next;
		i++;
	}
	pthread_create(&data.abyss_watcher, NULL, abyss_watcher_loop, &data);
	pthread_join(data.abyss_watcher, NULL);
	i = 0;
	while (i < infos.number_of_philosophers)
	{
		pthread_join(data.philo->thread, NULL);
		data.philo = data.philo->next;
		i++;
	}
	printf("finished\n");
	free_everything(&data);
	return (0);
}
