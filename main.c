/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:36:38 by nsauret           #+#    #+#             */
/*   Updated: 2025/01/07 16:34:47 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data			data;
	t_infos			infos;

	if (!parsing(&infos, argc, argv))
		return (1);
	data.infos = &infos;
	if (!create_philosopers(&data, &infos))
		return (free_everything(&data), 1);
	loop(&data);
	if (everyone_finished(data.philo))
		printf("finished\n");
	free_everything(&data);
	return (0);
}
