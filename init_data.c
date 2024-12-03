/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:49:01 by iboiraza          #+#    #+#             */
/*   Updated: 2024/11/29 10:09:36 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_input(t_philo *philo, char **argv)
{
	philo->nbr_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->max_meal = ft_atoi(argv[5]);
	else
		philo->max_meal = -1;
}

void	init_philos(t_philo *philos, t_table *table, t_mtx *forks,
		char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].meal_counter = 0;
		philos[i].eating = 0;
		init_input(&philos[i], argv);
		philos[i].start_time = get_current_time();
		philos[i].last_meal_time = get_current_time();
		philos[i].lock_write = &table->lock_write;
		philos[i].lock_dead = &table->lock_dead;
		philos[i].lock_meal = &table->lock_meal;
		philos[i].dead = &table->dead_flag;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[philos[i].nbr_philo - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(t_mtx *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_data(t_table *table, t_philo *philos)
{
	table->dead_flag = 0;
	table->philos = philos;
	pthread_mutex_init(&table->lock_write, NULL);
	pthread_mutex_init(&table->lock_dead, NULL);
	pthread_mutex_init(&table->lock_meal, NULL);
}
