/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:36:38 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/17 14:05:27 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*take_forks(void *void_philosopher)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *) void_philosopher;

	pthread_mutex_lock(&philosopher->fork_at_left);
	printf("philosopher %d took the fork at his left\n", philosopher->number);
	philosopher->hold_left_hand = 1;

	pthread_mutex_lock(&philosopher->fork_at_right);
	printf("philosopher %d took the fork at his right\n", philosopher->number);
	philosopher->hold_right_hand = 1;

	usleep(500000);

	pthread_mutex_unlock(&philosopher->fork_at_left);
	printf("philosopher %d put back the fork at his left\n", philosopher->number);
	philosopher->hold_left_hand = 0;

	pthread_mutex_unlock(&philosopher->fork_at_right);
	printf("philosopher %d put back the fork at his right\n", philosopher->number);
	philosopher->hold_right_hand = 0;
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	(void)argc;
	(void)argv;

	create_philosopers(&data, 2);
	while (1)
	{
		pthread_create(&data.philosopher->thread, NULL, take_forks, &data.philosopher);
		data.philosopher = data.philosopher->next;
	}
	// while (1)
	// {
	// 	pthread_join(data.philosopher->thread, NULL);
	// 	data.philosopher = data.philosopher->next;
	// }
	// // pthread_mutex_destroy(&data.mutex);
	return (0);
}
