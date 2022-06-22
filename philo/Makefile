# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 12:49:19 by cjulienn          #+#    #+#              #
#    Updated: 2022/04/22 13:15:54 by cjulienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ./actions.c \
	   ./check_args.c \
	   ./free.c \
	   ./init_structs.c \
	   ./msgs.c \
	   ./main.c \
	   ./routines.c \
	   ./time.c \
	   ./utils.c

OBJS = $(SRCS:.c=.o)

INCLUDE_PATH = .

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_PATH)

RM = rm -f

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)
	@echo $(NAME) successfully made !!!

all: $(NAME)

clean:
	$(RM) $(OBJS)
	
fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
