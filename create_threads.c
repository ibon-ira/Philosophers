/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:26:56 by iboiraza          #+#    #+#             */
/*   Updated: 2024/11/27 10:41:40 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_dead);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->lock_dead), 1);
	pthread_mutex_unlock(philo->lock_dead);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (pointer);
}

int	ft_pthread_create(t_table *table, t_mtx *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, table->philos) != 0)
		destroy_all("Thread creation error", table, forks);
	i = 0;
	while (i < table->philos[0].nbr_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &philo_routine,
				&table->philos[i]) != 0)
			destroy_all("Thread creation error", table, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destroy_all("Thread join error", table, forks);
	while (i < table->philos[0].nbr_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			destroy_all("Thread join error", table, forks);
		i++;
	}
	return (0);
}
