# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhizdahr <zhizdahr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 17:22:57 by hirebbec          #+#    #+#              #
#    Updated: 2022/06/26 16:06:57 by zhizdahr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BONUS = philo_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

FILES_BONUS = main.c ft_atoi.c philo_life.c init.c philo_do.c
BONUS_FILES    =    $(addprefix bonus/, $(FILES_BONUS))
OBJS_BONUS = $(BONUS_FILES:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

all: $(NAME_BONUS)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re: fclean all

.PHONY:all clean fclean re
