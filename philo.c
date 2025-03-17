/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:42:56 by juanherr          #+#    #+#             */
/*   Updated: 2025/03/17 16:15:54 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data		data;
	t_philo		*philo;
	pthread_t	*threads;
	int			i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	data.number_of_philosophers = atoi(argv[1]);
	data.time_to_die = atoi(argv[2]);
	data.time_to_eat = atoi(argv[3]);
	data.time_to_sleep = atoi(argv[4]);
	data.all_have_eaten = 0;
	if (argc == 6)
		data.times_of_must_eat = atoi(argv[5]);
	else
		data.times_of_must_eat = -1;
	data.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data.number_of_philosophers);
	if (!data.forks)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_mutex_init(&data.forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data.meal_mutex, NULL);
	philo = (t_philo *)malloc(sizeof(t_philo) * data.number_of_philosophers);
	if (!philo)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	threads = (pthread_t *)malloc(sizeof(pthread_t)
			* data.number_of_philosophers);
	if (!threads)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		philo[i].id = i;
		philo[i].meals = 0;
		philo[i].last_meal = get_time();
		philo[i].data = &data;
		pthread_create(&threads[i], NULL, simulation, &philo[i]);
		i++;
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
        pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
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
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d died 💀\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		return (NULL);
	}
	while (1)
	{
		if (philo->data->stop_simulation)
			break ;
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d is thinking\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		usleep(philo->data->time_to_sleep * 1000);
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
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
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d is sleeping\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		usleep(philo->data->time_to_sleep * 1000);
		if (check_end(philo))
			break ;
	}
	return (NULL);
}

int	check_end(t_philo *philo)
{
	if (philo->data->times_of_must_eat != -1
		&& philo->meals >= philo->data->times_of_must_eat)
	{
		pthread_mutex_lock(&philo->data->eat_count_mutex);
		philo->data->all_have_eaten++;
		if (philo->data->all_have_eaten >= philo->data->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->data->print_mutex);
			printf("%ld All philosophers are full 🥱\n", get_time());
			pthread_mutex_unlock(&philo->data->print_mutex);
			philo->data->stop_simulation = 1;
			pthread_mutex_unlock(&philo->data->eat_count_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->eat_count_mutex);
	}
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (get_time() - philo->last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d died 💀\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		philo->data->stop_simulation = 1;
		pthread_mutex_unlock(&philo->data->meal_mutex);
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
        pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % philo->data->number_of_philosophers]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (0);
}

size_t	get_time(void) //in milliseconds
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
