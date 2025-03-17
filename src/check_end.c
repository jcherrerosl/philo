/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:54:45 by juanherr          #+#    #+#             */
/*   Updated: 2025/03/17 22:01:39 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philosophers_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_count_mutex);
	philo->data->all_have_eaten++;
	if (philo->data->all_have_eaten >= philo->data->number_of_philosophers)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld All philosophers are full 🥱\n", get_time());
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(&philo->data->meal_mutex);
		philo->data->stop_simulation = 1;
		pthread_mutex_unlock(&philo->data->meal_mutex);
		pthread_mutex_unlock(&philo->data->eat_count_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eat_count_mutex);
	return (0);
}

int	philosopher_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d died 💀\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->data->stop_simulation = 1;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (1);
}

int	check_end(t_philo *philo)
{
	if (philo->data->times_of_must_eat != -1
		&& philo->meals >= philo->data->times_of_must_eat)
	{
		if (all_philosophers_full(philo))
			return (1);
	}
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (get_time() - philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		return (philosopher_died(philo));
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (0);
}
