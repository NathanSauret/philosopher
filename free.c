/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:32:15 by nsauret           #+#    #+#             */
/*   Updated: 2025/01/14 15:27:50 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_everything(t_data *data)
{
	t_philosopher	*philo;
	t_philosopher	*next_philo;
	int				i;

	philo = data->philo;
	i = 0;
	while (i < data->last_philo_number)
	{
		next_philo = philo->next;
		pthread_mutex_destroy(&philo->mutex_last_eat_time);
		pthread_mutex_destroy(&philo->fork_at_right);
		free(philo);
		philo = next_philo;
		i++;
	}
	pthread_mutex_destroy(&data->infos->mutex_someone_died);
	pthread_mutex_destroy(&data->infos->mutex_start_signal);
	pthread_mutex_destroy(&data->infos->write_mutex);
}
