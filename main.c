/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:36:38 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/23 18:00:18 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philosopher_loop(void *void_philo)
{
	t_philosopher	*philo;
	int				i;

	philo = (t_philosopher *) void_philo;
	if (philo->number % 2 == 0)
		usleep(30);
	i = 0;
	while (i != philo->infos.nbr_must_eat)
	{
		pthread_mutex_lock(philo->fork_at_left);
		philo->hold_left_hand = 1;
		display_message(philo, 0);

		pthread_mutex_lock(&philo->fork_at_right);
		philo->hold_right_hand = 1;
		display_message(philo, 0);

		display_message(philo, 1);
		usleep(philo->infos.time_to_eat);

		pthread_mutex_unlock(philo->fork_at_left);
		philo->hold_left_hand = 0;

		pthread_mutex_unlock(&philo->fork_at_right);
		philo->hold_right_hand = 0;

		display_message(philo, 2);
		usleep(philo->infos.time_to_sleep);

		display_message(philo, 3);
		usleep(100);
		i++;
	}
	return (NULL);
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
	// printf("time start: %ld\n", data.philo->infos.time_start);
	// printf("time passed from start: %ld\n", get_time() - data.philo->infos.time_start);
	// printf("number of philosophers: %d\n", data.philo->infos.number_of_philosophers);
	// printf("time to die: %ld\n", data.philo->infos.time_to_die);
	// printf("time to eat: %ld\n", data.philo->infos.time_to_eat);
	// printf("time to sleep: %ld\n", data.philo->infos.time_to_sleep);
	// printf("number of time each philosopher must eat: %d\n", data.philo->infos.nbr_must_eat);
	tmp_philo = data.philo;
	i = 0;
	while (i < infos.number_of_philosophers)
	{
		pthread_create(&tmp_philo->thread, NULL, philosopher_loop, tmp_philo);
		tmp_philo = tmp_philo->next;
		i++;
	}
	i = 0;
	while (i < infos.number_of_philosophers)
	{
		pthread_join(data.philo ->thread, NULL);
		data.philo = data.philo->next;
		i++;
	}
	free_everything(&data);
	printf("finished\n");
	return (0);
}
