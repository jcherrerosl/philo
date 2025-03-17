/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:42:04 by juanherr          #+#    #+#             */
/*   Updated: 2025/03/17 22:22:51 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				number_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	ssize_t			times_of_must_eat;
	int				all_have_eaten;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	eat_count_mutex;
	int				stop_simulation;
	pthread_mutex_t	print_mutex;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	size_t			last_meal;
	struct s_data	*data;
}					t_philo;

//check_end.c
int					all_philosophers_full(t_philo *philo);
int					philosopher_died(t_philo *philo);
int					check_end(t_philo *philo);

//utils.c
size_t				get_time(void);
int					handle_malloc_error(void *ptr);
void				ft_usleep(size_t ms, t_data *data);

//simulation.c
void				philo_think(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_eat(t_philo *philo, int left_fork, int right_fork);
void				one_philosopher(t_philo *philo);
void				*simulation(void *arg);

//forks.c
void				take_forks(t_philo *philo, int left_fork, int right_fork);

//philo.c
void				init_data(t_data *data, int argc, char *argv[]);
t_philo				*init_philos(t_data *data);
int					start_simulation(t_data *data, t_philo *philo);
int					usage(int argc);

#endif