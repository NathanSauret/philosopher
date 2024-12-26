/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:11:04 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/26 15:22:42 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_take_fork(t_philosopher *philo, pthread_mutex_t *fork)
{
	if (!fork || philo->infos->someone_died)
	{
		exit_table(philo);
		return (0);
	}
	pthread_mutex_lock(fork);
	if (fork == philo->fork_at_left)
		philo->hold_left_hand = 1;
	else if (fork == &philo->fork_at_right)
		philo->hold_right_hand = 1;
	display_message(philo, FORK_TAKEN_MSG);
	return (1);
}

int	safe_put_down_fork(t_philosopher *philo, pthread_mutex_t *fork)
{
	if (philo->infos->someone_died)
	{
		exit_table(philo);
		return (0);
	}
	pthread_mutex_unlock(fork);
	if (fork == philo->fork_at_left)
		philo->hold_left_hand = 0;
	else if (fork == &philo->fork_at_right)
		philo->hold_right_hand = 0;
	return (1);
}

int	safe_eating(t_philosopher *philo)
{
	if (philo->infos->someone_died)
	{
		exit_table(philo);
		return (0);
	}
	philo->last_eat_time = get_time();
	display_message(philo, EATING_MSG);
	ft_usleep(philo->infos->time_to_eat, philo->infos);
	return (1);
}

int	safe_sleeping(t_philosopher *philo)
{
	if (philo->infos->someone_died)
	{
		exit_table(philo);
		return (0);
	}
	display_message(philo, SLEEPING_MSG);
	ft_usleep(philo->infos->time_to_sleep, philo->infos);
	return (1);
}

int	safe_thinking(t_philosopher *philo)
{
	if (philo->infos->someone_died)
	{
		exit_table(philo);
		return (0);
	}
	display_message(philo, THINKING_MSG);
	return (1);
}