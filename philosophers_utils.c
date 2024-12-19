/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:55:52 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/19 15:28:36 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philosopher	*get_philosopher(t_data *data, int number)
{
	t_philosopher	*specific_philosopher;

	specific_philosopher = data->philosopher;
	while (specific_philosopher->number != number)
	{
		if (!specific_philosopher)
			return (NULL);
		if (number < specific_philosopher->number)
			specific_philosopher = specific_philosopher->prev;
		else
			specific_philosopher = specific_philosopher->next;
	}
	return (specific_philosopher);
}

static t_philosopher	*new_philosopher(t_data *data)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->time_start = data->time_start;
	philosopher->last_eat_time = 0;
	pthread_mutex_init(&philosopher->fork_at_right, NULL);
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

	data->time_start = get_time();
	i = 0;
	while (i < number_of_philosophers)
	{
		data->philosopher = new_philosopher(data);
		if (i != 0)
		{
			data->philosopher->prev = prev_philosopher;
			data->philosopher->prev->next = data->philosopher;
			data->philosopher->fork_at_left = &data->philosopher->prev->fork_at_right;
		}
		data->philosopher->number = i + 1;
		prev_philosopher = data->philosopher;
		i++;
	}
	data->philosopher->next = get_philosopher(data, 1);
	data->philosopher = data->philosopher->next;
	data->philosopher->prev = get_philosopher(data, number_of_philosophers);
	data->philosopher->fork_at_left = &data->philosopher->prev->fork_at_right;
}
