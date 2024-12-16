/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:43:03 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/16 16:35:27 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

//state: 0=eating; 1=sleeping; 2=thinking
typedef struct s_philosopher
{
	int						number;
	int						state;
	int						fork_at_left;
	int						fork_at_right;
	int						left_hand;
	int						right_hand;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
}	t_philosopher;

typedef struct s_data
{
	t_philosopher	*philosopher;
	struct timeval	tv;
	struct timezone	tz;
}	t_data;

// philosopher_utils.c
void	display_philosopher(t_philosopher *philosopher);
void	create_philosopers(t_data *data, int number_of_philosophers);

#endif
