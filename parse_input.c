/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:27:21 by iboiraza          #+#    #+#             */
/*   Updated: 2024/11/29 10:03:04 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	error_syntax(char *str_nbr)
{
	if (!(*str_nbr == '+' || (*str_nbr >= '0' && *str_nbr <= '9')))
		return (1);
	if ((*str_nbr == '+')
		&& !(str_nbr[1] >= '0' && str_nbr[1] <= '9'))
		return (1);
	while (*++str_nbr)
	{
		if (!(*str_nbr >= '0' && *str_nbr <= '9'))
			return (1);
	}
	return (0);
}

void	parse_input(char **argv)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (error_syntax(argv[i]))
			error_exit(YELLOW"Please write positive numbers"RST);
		if (ft_atoi(argv[i]) == 0)
			error_exit(YELLOW"Please write positive numbers"RST);
		if (ft_strlen(argv[i]) > 9)
			error_exit(CYAN"Please write smaller numbers"RST);
		i++;
	}
	if (argv[5] != NULL)
	{
		if (error_syntax(argv[i]))
			error_exit(YELLOW"Please write positive numbers"RST);
		if (ft_atoi(argv[5]) == 0)
			error_exit(YELLOW"Please write positive numbers"RST);
		if (ft_strlen(argv[i]) > 9)
			error_exit(CYAN"Please write smaller numbers"RST);
	}
	if (ft_atoi(argv[1]) > PHILO_MAX)
		error_exit(MAGENTA"Too much philosophers( ͠❛ ₃ ͡❛)"RST);
	return ;
}
