/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:42:34 by juanherr          #+#    #+#             */
/*   Updated: 2025/03/17 21:23:00 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void) //in milliseconds
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	handle_malloc_error(void *ptr)
{
	if (!ptr)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	return (0);
}
