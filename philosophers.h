/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:43:03 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/23 17:55:17 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_infos
{
	long			time_start;
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_must_eat;
}	t_infos;

//state: 0=waiting_to_eat; 1=eating; 2=sleeping; 3=thinking
typedef struct s_philosopher
{
	t_infos					infos;
	pthread_t				thread;
	int						number;
	int						last_eat_time;
	pthread_mutex_t			fork_at_right;
	pthread_mutex_t			*fork_at_left;
	int						hold_left_hand;
	int						hold_right_hand;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
}	t_philosopher;

typedef struct s_data
{
	t_philosopher		*philo;
	t_infos				infos;
	int					last_philo_number;
}	t_data;

// debug.c
void			display_philosopher(t_philosopher *philosopher);
void			display_table(t_philosopher *philo_input);

// free
void			free_everything(t_data *data);

// parsing.c
int				parsing(t_data *data, t_infos *infos, int argc, char **argv);

// philosopher_utils.c
t_philosopher	*get_philosopher(t_data *data, int number);
int				create_philosopers(t_data *data, t_infos *infos);

// utils.c
long			get_time(void);
void			display_message(t_philosopher *philo, int status);

#endif
