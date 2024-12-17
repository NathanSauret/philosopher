/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:34:24 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/17 13:45:29 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	display_philosopher(t_philosopher *philosopher)
{
	printf("~~~\n");
	printf("number: %d\n", philosopher->number);
	if (philosopher->state == 0)
		printf("state: waiting to eat\n");
	else if (philosopher->state == 1)
		printf("state: eating\n");
	else if (philosopher->state == 2)
		printf("state: sleeping\n");
	else if (philosopher->state == 3)
		printf("state: thinking\n");
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
