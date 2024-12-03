# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 09:51:12 by iboiraza          #+#    #+#              #
#    Updated: 2024/11/29 10:08:14 by iboiraza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC		= cc
CFLAGS		= -Wall -Wextra -Werror
NAME		= philo
RM		= rm -rf

CFILES = main.c  init_data.c parse_input.c utils.c monitor.c philo_actions.c \
		create_threads.c time_utils.c

OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME) : $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)


clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
