/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:21:56 by juanherr          #+#    #+#             */
/*   Updated: 2025/03/17 22:24:53 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo, int left_fork, int right_fork)
{
	if (philo->data->number_of_philosophers == 2 && philo->id % 2 == 1)
		usleep(philo->data->time_to_eat * 1000);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
}
