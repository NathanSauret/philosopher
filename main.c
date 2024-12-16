/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:36:38 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/16 16:28:05 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	create_philosopers(&data, 20);
	while (data.philosopher->next)
	{
		display_philosopher(data.philosopher);
		data.philosopher = data.philosopher->next;
	}
	return (0);
}
