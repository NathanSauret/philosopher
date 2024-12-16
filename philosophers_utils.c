/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:55:52 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/16 16:38:16 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	display_philosopher(t_philosopher *philosopher)
{
	printf("~~~\n");
	printf("number: %d\n", philosopher->number);
	if (philosopher->state == 0)
		printf("state: eating\n");
	if (philosopher->state == 1)
		printf("state: sleeping\n");
	if (philosopher->state == 2)
		printf("state: thinking\n");
	if (philosopher->fork_at_left)
		printf("fork at left: yes\n");
	else
		printf("fork at left: no\n");
	if (philosopher->fork_at_right)
		printf("fork at right: yes\n");
	else
		printf("fork at right: no\n");
	if (philosopher->left_hand)
		printf("fork in left hand: yes\n");
	else
		printf("fork in left hand: no\n");
	if (philosopher->right_hand)
		printf("fork in right hand: yes\n");
	else
		printf("fork in right hand: no\n");
	printf("~~~\n");
}

static t_philosopher	*new_philosopher()
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->state = 1;
	philosopher->fork_at_right = 1;
	philosopher->left_hand = 0;
	philosopher->right_hand = 0;
	philosopher->next = NULL;
	philosopher->prev = NULL;
	return (philosopher);
}

void	create_philosopers(t_data *data, int number_of_philosophers)
{
	int				i;
	t_philosopher	*prev_philosopher;

	i = 0;
	while (i < number_of_philosophers)
	{
		// create his fork (right)
		data->philosopher = new_philosopher();
		if (i != 0)
		{
			data->philosopher->prev = prev_philosopher;
			data->philosopher->prev->next = data->philosopher;
			// his left fork is his left neighbor's one
		}
		data->philosopher->number = i + 1;
		prev_philosopher = data->philosopher;
		i++;
	}
	while (data->philosopher->prev)
		data->philosopher = data->philosopher->prev;
	// left fork = last one
}
