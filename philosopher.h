/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:43:03 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/17 13:47:50 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

//state: 0=waiting_to_eat; 1=eating; 2=sleeping; 3=thinking
typedef struct s_philosopher
{
	pthread_t				thread;
	int						number;
	int						state;
	pthread_mutex_t			fork_at_left;
	pthread_mutex_t			fork_at_right;
	int						hold_left_hand;
	int						hold_right_hand;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
}	t_philosopher;

typedef struct s_data
{
	t_philosopher	*philosopher;
	struct timeval	tv;
	struct timezone	tz;
}	t_data;

// debug.c
void			display_philosopher(t_philosopher *philosopher);

// philosopher_utils.c
t_philosopher	*get_philosopher(t_data *data, int number);
void			create_philosopers(t_data *data, int number_of_philosophers);

#endif
