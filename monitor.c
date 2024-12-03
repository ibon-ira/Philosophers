/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:57:34 by iboiraza          #+#    #+#             */
/*   Updated: 2024/11/29 10:05:04 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->lock_write);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->lock_write);
}

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->lock_meal);
	if (get_current_time() - philo->last_meal_time >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->lock_meal), 1);
	pthread_mutex_unlock(philo->lock_meal);
	return (0);
}

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nbr_philo)
	{
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			print_message("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].lock_dead);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].lock_dead);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].max_meal == -1)
		return (0);
	while (i < philos[0].nbr_philo)
	{
		pthread_mutex_lock(philos[i].lock_meal);
		if (philos[i].meal_counter >= philos[i].max_meal)
			finished_eating++;
		pthread_mutex_unlock(philos[i].lock_meal);
		i++;
	}
	if (finished_eating == philos[0].nbr_philo)
	{
		pthread_mutex_lock(philos[0].lock_dead);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].lock_dead);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	return (pointer);
}
