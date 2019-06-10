# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/19 23:12:54 by tdautrem     #+#   ##    ##    #+#        #
#    Updated: 2019/02/13 16:03:25 by tvarnier    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

CC = gcc

NAME = lem-in

SRCS = 	 srcs/main.c \
		 srcs/struct.c \
		 srcs/pr_main.c \
		 srcs/pr_room.c \
		 srcs/pr_link.c \
		 srcs/pr_rm_space.c \
		 srcs/anthill.c \
		 srcs/solver.c \
		 srcs/sv_way_hot.c \
		 srcs/sv_send.c \
		 srcs/sv_send_move.c \
		 srcs/sv_way_tab.c \
		 srcs/sv_struct.c

HEADERS = includes/lem_in.h

FLAGS = -Wall -Wextra -Werror -g

OBJ = $(SRCS:.c=.o)

LIB = libft/libft.a

all: $(LIB) $(NAME)

$(LIB):
		make -C libft

$(NAME): $(OBJ)
		$(CC) -I includes -o $@ $^ $(LIB) $(FLAGS)

%.o: %.c
		$(CC) -I includes/ -o $@ -c $< $(FLAGS)

clean:
		rm -rf $(OBJ)
		make -C libft clean

fclean: clean
		rm -rf $(NAME)
		rm -rf $(LIB)

re: fclean all
