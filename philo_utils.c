/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:55:52 by nsauret           #+#    #+#             */
/*   Updated: 2025/01/14 15:33:00 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_table(t_philosopher *philo)
{
	if (philo->hold_right_hand)
		pthread_mutex_unlock(&philo->fork_at_right);
	if (philo->hold_left_hand)
		pthread_mutex_unlock(philo->fork_at_left);
}

t_philosopher	*get_philosopher(t_data *data, int number)
{
	t_philosopher	*specific_philo;

	specific_philo = data->philo;
	if (!specific_philo)
		return (NULL);
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
		return (print_error(MALLOC_ERROR), NULL);
	philo->infos = infos;
	if (pthread_mutex_init(&philo->mutex_last_eat_time, NULL))
	{
		free(philo);
		return (print_error(MUTEX_ERROR), NULL);
	}
	philo->last_eat_time = get_time();
	if (pthread_mutex_init(&philo->fork_at_right, NULL))
	{
		pthread_mutex_destroy(&philo->mutex_last_eat_time);
		free(philo);
		return (print_error(MUTEX_ERROR), NULL);
	}
	philo->hold_left_hand = 0;
	philo->hold_right_hand = 0;
	philo->finished = 0;
	philo->next = NULL;
	philo->prev = NULL;
	return (philo);
}

static void	last_actions(t_data *data, t_infos *infos)
{
	data->philo->next = get_philosopher(data, 1);
	data->philo = data->philo->next;
	data->philo->prev = get_philosopher(data, infos->number_of_philosophers);
	if (data->infos->number_of_philosophers > 1)
		data->philo->fork_at_left = &data->philo->prev->fork_at_right;
	else
		data->philo->fork_at_left = NULL;
}

int	create_philosopers(t_data *data, t_infos *infos)
{
	int				i;
	t_philosopher	*prev_philo;

	infos->time_start = get_time();
	data->last_philo_number = 0;
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
	last_actions(data, infos);
	return (1);
}
