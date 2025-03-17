/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:42:04 by juanherr          #+#    #+#             */
/*   Updated: 2025/03/17 16:26:57 by juanherr         ###   ########.fr       */
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
	pthread_mutex_t print_mutex;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals;		
	size_t			last_meal;
	struct s_data	*data;
}					t_philo;

size_t				get_time(void);
void				*simulation(void *arg);
int					check_end(t_philo *philo);

#endif