# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/19 23:12:54 by tdautrem     #+#   ##    ##    #+#        #
#    Updated: 2018/11/02 06:30:39 by tdautrem    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

C = gcc

NAME = libftprintf.a

SRCS = srcs/ft_printf_main.c \
	   srcs/ft_printf.c \
	   srcs/ft_format_save.c \
	   srcs/ft_format_main.c \
	   srcs/ft_lstprintf.c \
	   srcs/ft_convert_fnc.c \
	   srcs/ft_convert_fnc1.c \
	   srcs/ft_convert_fnc2.c \
	   srcs/ft_convert_fnc3.c \
	   srcs/ft_convert_main.c \
	   srcs/ft_modifier_main.c \
	   srcs/ft_format_fnc.c \
	   srcs/ft_color_main.c \

FLAGS = -Wall -Wextra -Werror -g

OBJ = $(SRCS:.c=.o)

LIB = libft/libft.a

all: $(NAME)

$(LIB):
		make -C libft

$(NAME): $(LIB) $(OBJ)
		cp libft/libft.a $(NAME)
		ar rcs $(NAME) $(OBJ) $(LIB)

%.o: %.c
		$(CC) -I includes/ -o $@ -c $< $(FLAGS)

clean:
		rm -rf $(OBJ)
		make -C libft clean

fclean: clean
		rm -rf $(NAME)
		rm -rf $(LIB)

re: fclean all
