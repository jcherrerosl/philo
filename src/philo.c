/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:42:56 by juanherr          #+#    #+#             */
/*   Updated: 2025/03/17 21:10:49 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, int argc, char *argv[])
{
	int	i;

	data->number_of_philosophers = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->all_have_eaten = 0;
	data->stop_simulation = 0;
	if (argc == 6)
		data->times_of_must_eat = atoi(argv[5]);
	else
		data->times_of_must_eat = -1;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (handle_malloc_error(data->forks))
		return ;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->eat_count_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (handle_malloc_error(philo))
		return (NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo[i].id = i;
		philo[i].meals = 0;
		philo[i].last_meal = get_time();
		philo[i].data = data;
		i++;
	}
	return (philo);
}

int	start_simulation(t_data *data, t_philo *philo)
{
	pthread_t	*threads;
	int			i;

	threads = (pthread_t *)malloc(sizeof(pthread_t)
			* data->number_of_philosophers);
	if (handle_malloc_error(threads))
		return (1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_create(&threads[i], NULL, simulation, &philo[i]);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	return (0);
}

int	usage(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;
	int		i;

	if (usage(argc))
		return (1);
	init_data(&data, argc, argv);
	philo = init_philos(&data);
	if (!philo)
		return (1);
	if (start_simulation(&data, philo))
		return (1);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data.meal_mutex);
	pthread_mutex_destroy(&data.eat_count_mutex);
	pthread_mutex_destroy(&data.print_mutex);
	free(data.forks);
	free(philo);
	return (0);
}
