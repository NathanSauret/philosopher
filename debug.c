/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:34:24 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/23 17:17:02 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_philosopher(t_philosopher *philo)
{
	printf("~~~\n");
	printf("number: %d\n", philo->number);
	if (philo->hold_left_hand)
		printf("fork in left hand: yes\n");
	else
		printf("fork in left hand: no\n");
	if (philo->hold_right_hand)
		printf("fork in right hand: yes\n");
	else
		printf("fork in right hand: no\n");
	printf("~~~\n");
}

void	display_table(t_philosopher *philo_input)
{
	t_philosopher	*philo;
	int				number_of_philosophers;
	int				i;

	philo = philo_input;
	while (philo->number != 1)
	{
		if (philo < 0)
			philo = philo->next;
		else
			philo = philo->prev;
	}
	number_of_philosophers = 2;

	i = 0;
	while (i < number_of_philosophers)
	{
		if (!philo->hold_left_hand && !philo->prev->hold_right_hand)
			printf(" 🍴 ");
		else
			printf("    ");
		printf("   ");
		philo = philo->next;
		i++;
	}
	if (!philo->prev->hold_right_hand && !philo->hold_left_hand)
		printf(" 🍴 ");
	else
		printf("    ");

	printf("\n");

	i = 0;
	while (i < number_of_philosophers)
	{
		if (philo->hold_left_hand)
			printf("  🍴");
		else
			printf("    ");
		printf("-%d-", philo->number);
		if (philo->hold_right_hand)
			printf("🍴  ");
		philo = philo->next;
		i++;
	}
	printf("\n");
}
