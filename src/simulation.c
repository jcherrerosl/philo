/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:57:03 by juanherr          #+#    #+#             */
/*   Updated: 2025/03/17 22:33:49 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d is thinking\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d is sleeping\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_eat(t_philo *philo, int left_fork, int right_fork)
{
	if (philo->data->number_of_philosophers == 2 && philo->id % 2 == 1)
		usleep(1000);
	take_forks(philo, left_fork, right_fork);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d is eating\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
}

void	one_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d has taken a fork\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d died 💀\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
}

void	*simulation(void *arg)
{
	t_philo	*philo;
	int		left_fork;
	int		right_fork;

	philo = (t_philo *)arg;
	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->data->number_of_philosophers;
	if (philo->data->number_of_philosophers == 1)
	{
		one_philosopher(philo);
		return (NULL);
	}
	while (1)
	{
		if (philo->data->stop_simulation)
			break ;
		philo_think(philo);
		philo_eat(philo, left_fork, right_fork);
		philo_sleep(philo);
		if (check_end(philo))
			break ;
	}
	return (NULL);
}
