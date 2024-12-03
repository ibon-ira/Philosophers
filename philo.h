/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:51:33 by iboiraza          #+#    #+#             */
/*   Updated: 2024/11/29 10:05:23 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define RST		"\033[0m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define MAGENTA	"\033[1;35m"
# define CYAN		"\033[1;36m"
# define WHITE		"\033[1;37m"

# define PHILO_MAX 600

typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			eating;
	int			meal_counter;
	int			max_meal;
	long		last_meal_time;
	long		start_time;
	long		nbr_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			*dead;
	t_mtx		*lock_dead;
	t_mtx		*lock_write;
	t_mtx		*lock_meal;
	t_mtx		*left_fork;
	t_mtx		*right_fork;
}		t_philo;

typedef struct s_table
{
	int		dead_flag;
	t_mtx	lock_dead;
	t_mtx	lock_write;
	t_mtx	lock_meal;
	t_philo	*philos;
}		t_table;

void	error_exit(char *error);
int		ft_atoi(char *str);
void	parse_input(char **argv);
void	init_data(t_table *table, t_philo *philos);
void	init_forks(t_mtx *forks, int philo_num);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	destroy_all(char *str, t_table *table, t_mtx *forks);
int		ft_pthread_create(t_table *table, t_mtx *forks);
void	init_philos(t_philo *philos, t_table *table, t_mtx *forks,
			char **argv);
int		ft_strlen(char *str);
int		dead_loop(t_philo *philo);
void	print_message(char *str, t_philo *philo, int id);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	*monitor(void *pointer);

#endif
