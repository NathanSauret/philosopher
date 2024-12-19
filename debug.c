/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:34:24 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/19 15:25:35 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	display_philosopher(t_philosopher *philosopher)
{
	printf("~~~\n");
	printf("number: %d\n", philosopher->number);
	if (philosopher->hold_left_hand)
		printf("fork in left hand: yes\n");
	else
		printf("fork in left hand: no\n");
	if (philosopher->hold_right_hand)
		printf("fork in right hand: yes\n");
	else
		printf("fork in right hand: no\n");
	printf("~~~\n");
}

void	display_table(t_philosopher *philo_input)
{
	t_philosopher	*philosopher;
	int				number_of_philosopher;
	int				i;

	philosopher = philo_input;
	while (philosopher->number != 1)
	{
		if (philosopher < 0)
			philosopher = philosopher->next;
		else
			philosopher = philosopher->prev;
	}
	number_of_philosopher = 2;

	i = 0;
	while (i < number_of_philosopher)
	{
		if (!philosopher->hold_left_hand && !philosopher->prev->hold_right_hand)
			printf(" 🍴 ");
		else
			printf("    ");
		printf("   ");
		philosopher = philosopher->next;
		i++;
	}
	if (!philosopher->prev->hold_right_hand && !philosopher->hold_left_hand)
		printf(" 🍴 ");
	else
		printf("    ");

	printf("\n");

	i = 0;
	while (i < number_of_philosopher)
	{
		if (philosopher->hold_left_hand)
			printf("  🍴");
		else
			printf("    ");
		printf("-%d-", philosopher->number);
		if (philosopher->hold_right_hand)
			printf("🍴  ");
		philosopher = philosopher->next;
		i++;
	}
	printf("\n");
}
