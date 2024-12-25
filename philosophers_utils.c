/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:55:52 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/25 17:37:02 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosopher	*get_philosopher(t_data *data, int number)
{
	t_philosopher	*specific_philo;

	specific_philo = data->philo;
	while (specific_philo->number != number)
	{
		if (!specific_philo)
			return (NULL);
		if (number < specific_philo->number)
			specific_philo = specific_philo->prev;
		else
			specific_philo = specific_philo->next;
	}
	return (specific_philo);
}

static t_philosopher	*new_philosopher(t_infos *infos)
{
	t_philosopher		*philo;

	philo = malloc(sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	philo->infos = infos;
	philo->last_eat_time = infos->time_start;
	pthread_mutex_init(&philo->fork_at_right, NULL);
	philo->hold_left_hand = 0;
	philo->hold_right_hand = 0;
	philo->finished = 0;
	philo->next = NULL;
	philo->prev = NULL;
	return (philo);
}

int	create_philosopers(t_data *data, t_infos *infos)
{
	int				i;
	t_philosopher	*prev_philo;

	infos->time_start = get_time();
	i = 0;
	while (i < infos->number_of_philosophers)
	{
		data->philo = new_philosopher(infos);
		if (!data->philo)
			return (data->philo = get_philosopher(data, 1), 0);
		if (i != 0)
		{
			data->philo->prev = prev_philo;
			data->philo->prev->next = data->philo;
			data->philo->fork_at_left = &data->philo->prev->fork_at_right;
		}
		data->philo->number = ++i;
		data->last_philo_number = data->philo->number;
		prev_philo = data->philo;
	}
	data->philo->next = get_philosopher(data, 1);
	data->philo = data->philo->next;
	data->philo->prev = get_philosopher(data, infos->number_of_philosophers);
	data->philo->fork_at_left = &data->philo->prev->fork_at_right;
	return (1);
}
