/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:43:03 by nsauret           #+#    #+#             */
/*   Updated: 2025/01/06 18:29:56 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

# define FORK_TAKEN_MSG	0
# define EATING_MSG		1
# define SLEEPING_MSG	2
# define THINKING_MSG	3
# define DEAD_MSG		4
# define RESET			"\033[0m"
# define BOLD_RED		"\033[1;31m"
# define BLUE			"\033[34m"
# define GREEN			"\033[0;32m"
# define PURPLE			"\033[0;35m"

typedef struct s_infos
{
	pthread_mutex_t	write_mutex;
	int				start_signal;
	long			time_start;
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_must_eat;
	pthread_mutex_t	mutex_someone_died;
	int				someone_died;
}	t_infos;

//state: 0=waiting_to_eat; 1=eating; 2=sleeping; 3=thinking
typedef struct s_philosopher
{
	t_infos					*infos;
	pthread_t				thread;
	int						number;
	long					last_eat_time;
	pthread_mutex_t			fork_at_right;
	pthread_mutex_t			*fork_at_left;
	int						hold_left_hand;
	int						hold_right_hand;
	int						finished;
	struct s_philosopher	*next;
	struct s_philosopher	*prev;
}	t_philosopher;

typedef struct s_data
{
	t_philosopher		*philo;
	t_infos				*infos;
	pthread_t			abyss_watcher;
	int					last_philo_number;
}	t_data;

// abyss_watcher.c
void			*abyss_watcher_loop(void *void_philo);

// debug.c
void			display_table(t_philosopher *philo_input);

// free
void			free_everything(t_data *data);

// loop.c
void			loop(t_data	*data);

// parsing.c
int				parsing(t_infos *infos, int argc, char **argv);

// philo_utils.c
void			exit_table(t_philosopher *philo);
t_philosopher	*get_philosopher(t_data *data, int number);
int				create_philosopers(t_data *data, t_infos *infos);

// safe_actions.c
int				safe_take_fork(t_philosopher *philo, pthread_mutex_t *fork);
int				safe_put_down_fork(t_philosopher *philo, pthread_mutex_t *fork);
int				safe_eating(t_philosopher *philo);
int				safe_sleeping(t_philosopher *philo);
int				safe_thinking(t_philosopher *philo);

// utils.c
void			ft_usleep(long milliseconds, t_infos *infos);
int				everyone_finished(t_philosopher *philo);
long			get_time(void);
void			display_message(t_philosopher *philo, int status);

#endif
