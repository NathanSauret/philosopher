/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:55:52 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/17 14:01:14 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philosopher	*get_philosopher(t_data *data, int number)
{
	t_philosopher	*specific_philosopher;
	int				backward;

	backward = 0;
	specific_philosopher = data->philosopher;
	while (specific_philosopher->number != number)
	{
		if (!specific_philosopher->next)
			backward = 1;
		if (backward)
			specific_philosopher = specific_philosopher->prev;
		else
			specific_philosopher = specific_philosopher->next;
	}
	return (specific_philosopher);
}

static t_philosopher	*new_philosopher(void)
{
	t_philosopher	*philosopher;
	pthread_mutex_t	right_fork;
	pthread_t		thread;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	thread = 0;
	philosopher->thread = thread;
	philosopher->state = 0;
	pthread_mutex_init(&right_fork, NULL);
	philosopher->fork_at_right = right_fork;
	philosopher->hold_left_hand = 0;
	philosopher->hold_right_hand = 0;
	philosopher->next = NULL;
	philosopher->prev = NULL;
	return (philosopher);
}

void	create_philosopers(t_data *data, int number_of_philosophers)
{
	int				i;
	t_philosopher	*prev_philosopher;

	i = 0;
	while (i < number_of_philosophers)
	{
		data->philosopher = new_philosopher();
		if (i != 0)
		{
			data->philosopher->prev = prev_philosopher;
			data->philosopher->prev->next = data->philosopher;
			data->philosopher->fork_at_left = data->philosopher->prev->fork_at_right;
		}
		data->philosopher->number = i + 1;
		prev_philosopher = data->philosopher;
		i++;
	}
	data->philosopher->next = get_philosopher(data, 1);
	data->philosopher = get_philosopher(data, 1);
	data->philosopher->prev = get_philosopher(data, number_of_philosophers);
	data->philosopher->fork_at_left = data->philosopher->prev->fork_at_right;
}
