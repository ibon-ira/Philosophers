/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:50:33 by iboiraza          #+#    #+#             */
/*   Updated: 2024/11/29 10:09:22 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_mtx	forks[PHILO_MAX];
	t_philo	philos[PHILO_MAX];

	if (argc >= 5 && argc <= 6)
	{
		parse_input(argv);
		init_data(&table, philos);
		init_forks(forks, ft_atoi(argv[1]));
		init_philos(philos, &table, forks, argv);
		ft_pthread_create(&table, forks);
		destroy_all(NULL, &table, forks);
	}
	else
		error_exit(RED"Invalid number of arguments"RST);
	return (0);
}
