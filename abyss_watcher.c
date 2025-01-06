/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abyss_watcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:58:39 by nsauret           #+#    #+#             */
/*   Updated: 2025/01/06 18:19:40 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*abyss_watcher_loop(void *void_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) void_philo;
	while (!everyone_finished(philo))
	{
		if (!philo->finished
			&& get_time() - philo->last_eat_time > philo->infos->time_to_die)
		{
			pthread_mutex_lock(&philo->infos->mutex_someone_died);
			philo->infos->someone_died = 1;
			pthread_mutex_unlock(&philo->infos->mutex_someone_died);
			display_message(philo, DEAD_MSG);
			if (philo->hold_left_hand)
			{
				pthread_mutex_unlock(philo->fork_at_left);
				philo->hold_left_hand = 0;
			}
			if (philo->hold_right_hand)
			{
				pthread_mutex_unlock(&philo->fork_at_right);
				philo->hold_right_hand = 0;
			}
			return (NULL);
		}
		philo = philo->next;
	}
	return (NULL);
}
