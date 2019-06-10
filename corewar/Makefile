# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/12/10 21:06:37 by pduhard-     #+#   ##    ##    #+#        #
#    Updated: 2019/03/04 11:32:24 by pduhard-    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

##__________CONFIG__________#

NAME1		=	asm
NAME2		=	corewar

CC			=	gcc
FLAGS		=	-g -Wall -Werror -Wextra
LIB_FLAGS	=	-L $(LIB_PATH) $(LIB_FLAG) -lncurses
INCLUDES1	=	assembly/includes/asm.h
INCLUDES2	=	corewar_vm/includes/corewar.h

SRC1_PATH	=	./assembly/srcs/
SRC2_PATH	=	./corewar_vm/srcs/
BIN1_PATH	=	./assembly/bins/
BIN2_PATH	=	./corewar_vm/bins/
LIB_PATH	=	./libft/

SRC1		=	main.c					\
				ft_parsing.c			\
				ft_parseutils.c			\
				ft_assembler.c			\
				ft_free.c				\
				ft_get_id.c				\
				ft_check_id.c			\
				ft_param.c				\
				ft_param_utils.c		\
				ft_check_param.c		\
				ft_put_arg.c			\
				ft_put_arg_utils.c		\
				ft_put_id.c				\
				ft_print_option.c		\
	
SRC2		=	main.c					\
				ft_get.c				\
				ft_print.c				\
				ft_init.c				\
				ft_new.c				\
				ft_manage_process.c		\
				ft_live.c				\
				ft_store.c				\
				ft_load.c				\
				ft_add.c				\
				ft_sub.c				\
				ft_and.c				\
				ft_or.c					\
				ft_xor.c				\
				ft_zjmp.c				\
				ft_loadindex.c			\
				ft_storeindex.c			\
				ft_fork.c				\
				ft_longload.c			\
				ft_longloadindex.c		\
				ft_longfork.c			\
				ft_aff.c				\
				ft_operations.c			\
				ft_check_ocp.c			\
				ft_check_ocp2.c			\
				ft_free.c				\
				ft_args.c				\
				ft_instruction.c		\
				ft_loop.c				\
				ft_utils.c				\
				ft_ncurses_utils.c		\
				ft_ncurses_display.c	\
				ft_ncurses_end.c		\
				ft_ncurses_key.c		\
				ft_ncurses_main.c		\
				ft_ncurses_update.c     \
				ft_ncurses_next.c

BIN1			=	$(SRC1:.c=.o)
BIN2			=	$(SRC2:.c=.o)

LIB_FLAG			=	-lft
LIB					=	libft.a

SRCS1		=	$(addprefix $(SRC1_PATH), $(SRC1))
SRCS2		=	$(addprefix $(SRC2_PATH), $(SRC2))
BINS1		=	$(addprefix $(BIN1_PATH), $(BIN1))
BINS2		=	$(addprefix $(BIN2_PATH), $(BIN2))
LIBS		=	$(addprefix $(LIB_PATH), $(LIB))

.PHONY: all clean fclean re lib libft

#__________COLORS__________#

R			=	\033[0;31m
G			=	\033[32;7m
B			=	\033[0;34m
N			=	\33[0m

#__________RULES__________#

all: $(NAME1) $(NAME2)	
	
	@make -C libft


libft: $(LIBS)

$(NAME1): $(LIBS) $(BINS1)

	@$(CC) -I $(INCLUDES1) $(FLAGS) $(LIB_FLAGS) $^ -o $@
	@echo "\n\n$(B)[EXECUTABLE \"$(NAME1)\" READY]\n"

$(NAME2): $(LIBS) $(BINS2)

	@$(CC) -I $(INCLUDES2) $(FLAGS) $(LIB_FLAGS) $^ -o $@
	@echo "\n\n$(B)[EXECUTABLE \"$(NAME2)\" READY]\n"

$(LIBS):

	@make -C $(LIB_PATH)

$(BIN1_PATH)%.o: $(SRC1_PATH)%.c $(INCLUDES1) 

	@mkdir -p $(BIN1_PATH) || true
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $< && echo "${G} \c"

$(BIN2_PATH)%.o: $(SRC2_PATH)%.c $(INCLUDES2) 

	@mkdir -p $(BIN2_PATH) || true
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $< && echo "${G} \c"

clean:

	@make clean -C $(LIB_PATH)
	@echo "${R}[CLEANING $(NAME1) BINARIES]\n"
	@rm -Rf $(BIN1_PATH)
	@echo "${R}[CLEANING $(NAME2) BINARIES]\n"
	@rm -Rf $(BIN2_PATH)

fclean: clean

	@echo "${R}[REMOVING $(LIB)]"
	@rm -rf $(LIBS)
	@echo "\n${R}[REMOVING \"$(NAME1)\"]"
	@rm -f $(NAME1)
	@echo "\n${R}[REMOVING \"$(NAME2)\"]\n"
	@rm -f $(NAME2)

re: fclean all
