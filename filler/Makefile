# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/19 23:12:54 by tdautrem     #+#   ##    ##    #+#        #
#    Updated: 2018/11/24 04:10:44 by tdautrem    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

CC = gcc

FINAME = tdautrem.filler
VMNAME = tdautrem.VM


FISRCS = srcs/fi_main.c \
		 srcs/fi_coord_fnc.c \
		 srcs/fi_ia_motor.c \
		 srcs/fi_map_fnc.c \
		 srcs/fi_pos_sort.c \
		 srcs/fi_range_motor.c \

VMSRCS = srcs/vm_base_fnc.c \
	   srcs/vm_line_controller.c \
	   srcs/vm_motor.c \
	   srcs/vm_main.c \

FLAGS = -Wall -Wextra -Werror -g

FIOBJ = $(FISRCS:.c=.o)
VMOBJ = $(VMSRCS:.c=.o)

LIB = libft/libft.a

all: $(VMNAME) $(FINAME)

$(LIB):
		make -C libft

$(FINAME): $(FIOBJ)
		$(CC) -I includes -o $@ $^ $(LIB) $(FLAGS)

$(VMNAME): $(LIB) $(VMOBJ)
		$(CC) -I includes -o $@ $^ $(LIB) $(FLAGS)

%.o: %.c
		$(CC) -I includes/ -o $@ -c $< $(FLAGS)

clean:
		rm -rf $(VMOBJ)
		rm -rf $(FIOBJ)
		make -C libft clean

fclean: clean
		rm -rf $(VMNAME)
		rm -rf $(FINAME)
		rm -rf $(LIB)

re: fclean all
