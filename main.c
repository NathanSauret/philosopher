/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:36:38 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/19 15:50:51 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*philosopher_loop(void *void_philosopher)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *) void_philosopher;

	if (philosopher->number % 2 == 0)
		usleep(10);
	while (1)
	{
		pthread_mutex_lock(philosopher->fork_at_left);
		philosopher->hold_left_hand = 1;
		display_message(philosopher, 0);

		pthread_mutex_lock(&philosopher->fork_at_right);
		philosopher->hold_right_hand = 1;
		display_message(philosopher, 0);

		display_message(philosopher, 1);
		usleep(100);

		pthread_mutex_unlock(philosopher->fork_at_left);
		philosopher->hold_left_hand = 0;

		pthread_mutex_unlock(&philosopher->fork_at_right);
		philosopher->hold_right_hand = 0;

		display_message(philosopher, 2);
		usleep(100);

		display_message(philosopher, 3);
		usleep(100);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_data			data;
	t_philosopher	*tmp_philo;
	int				i;

	// parsing
	(void)argc;
	(void)argv;

	data.number_of_philosopher = 2;
	create_philosopers(&data, data.number_of_philosopher);
	tmp_philo = data.philosopher;
	i = 0;
	while (i < data.number_of_philosopher)
	{
		pthread_create(&tmp_philo->thread, NULL, philosopher_loop, tmp_philo);
		tmp_philo = tmp_philo->next;
		i++;
	}
	i = 0;
	while (i < data.number_of_philosopher)
	{
		pthread_join(data.philosopher->thread, NULL);
		data.philosopher = data.philosopher->next;
	}
	// pthread_mutex_destroy(&data.mutex);
	return (0);
}
