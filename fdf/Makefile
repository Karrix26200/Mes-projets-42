# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/19 23:12:54 by tdautrem     #+#   ##    ##    #+#        #
#    Updated: 2019/01/18 04:10:59 by tdautrem    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

CC = gcc

FDNAME = fdf

FDSRCS = srcs/fd_main.c \
		 srcs/fd_display.c \
		 srcs/fd_key.c \
		 srcs/fd_matrix.c \
		 srcs/pr_main.c \
		 srcs/pr_utils.c \

FLAGS = -Wall -Wextra -Werror -g

FDOBJ = $(FDSRCS:.c=.o)

LIB = libft/libft.a

LIBMLX = minilibx_macos/libmlx.a

FRAMEWORK = -framework OpenGL -framework AppKit

all: $(FDNAME)

$(LIB):
		make -C libft

$(LIBMLX):
		make -C minilibx_macos

$(FDNAME): $(LIB) $(LIBMLX) $(FDOBJ)
		$(CC) -I includes -o $@ $^ $(LIB) $(LIBMLX) $(FRAMEWORK) $(FLAGS)

%.o: %.c
		$(CC) -I includes/ -o $@ -c $< $(FLAGS)

clean:
		rm -rf $(FDOBJ)
		make -C libft clean
		make -C minilibx_macos clean

fclean: clean
		rm -rf $(FDNAME)
		rm -rf $(LIB)
		rm -rf $(LIBMLX)

re: fclean all
