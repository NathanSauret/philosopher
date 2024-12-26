/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abyss_watcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:58:39 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/26 15:26:10 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*abyss_watcher_loop(void *void_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) void_philo;
	while (!everyone_finished(philo))
	{
		if (get_time() - philo->last_eat_time > philo->infos->time_to_die)
		{
			philo->infos->someone_died = 1;
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
