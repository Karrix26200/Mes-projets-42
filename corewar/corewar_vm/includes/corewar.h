/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/10 22:15:28 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 11:58:11 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>

# include <ncurses.h>
# include <locale.h>
# include <sys/time.h>
# include "locale.h"

# define COLOR 0
# define GREEN "\033[0;38;2;49;151;32m"
# define BLUE "\033[0;38;2;27;42;187m"
# define RED "\033[0;38;2;195;19;19m"
# define YELLOW "\033[0;38;2;225;206;20m"
# define NONE "\033[0;38;2;123;123;123m"

# define BGREEN "\033[0;48;2;30;120;25m"
# define BBLUE "\033[0;48;2;20;32;152m"
# define BRED "\033[0;48;2;140;14;14m"
# define BYELLOW "\033[0;48;2;184;164;15m"
# define BNONE "\033[0;48;2;100;100;100m"

# define MAGIC_ERR "has a wrong exec magic number in his header\n"
# define SIZE_ERR "has a code size that differ from what its header says\n"

# define P_RUBY 203
# define P_EMERALD 42
# define P_SAPHIR 39
# define P_MAGEN 165

# define PP_RUBY 197
# define PP_EMERALD 48
# define PP_SAPHIR 45
# define PP_MAGEN 171

# define P_GOLD 220
# define I_BLUE 195

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3
# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define REG_NUMBER				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10
# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef char			t_arg_type;

typedef struct			s_co
{
	int					x;
	int					y;
}						t_co;

typedef struct			s_header
{
	unsigned int		magic;
	char				*prog_name;
	unsigned int		prog_size;
	char				*comment;
}						t_header;

typedef struct			s_mem
{
	unsigned char		byte;
	int					addr;
	int					player;
	struct s_mem		*next;
	struct s_mem		*prev;
	int					update_color;
}						t_mem;

typedef struct			s_process
{
	long				*reg;
	int					nb;
	int					carry;
	int					pc;
	int					live;
	int					last_live;
	int					lcycle;
	char				opcode;
	int					cast;
	int					player;
	struct s_process	*next;
	struct s_process	*prev;
	struct s_mem		*mem;
	struct s_mem		*mem_bu;
	struct s_mem		*instr;
}						t_process;

typedef struct			s_player
{
	int					nb;
	int					place;
	char				*buffer;
	int					size;
	char				*name;
	int					prog_size;
	char				*comment;
	int					aff;
	int					nb_live;
}						t_player;

typedef struct			s_op
{
	char				opcode;
	int					cast;
	void				(*ft)(t_process *process, t_mem *mem,
							int verb, t_player **players);
}						t_op;

typedef struct			s_ui
{
	int					line_len;
	int					line_marge;
	int					speed;
	int					pause;
	int					tpt;
}						t_ui;

typedef struct			s_vm
{
	t_mem				*mem;
	t_player			**players;
	t_process			*process;
	t_op				**instructions;
	int					death;
	int					nb_players;
	int					cycle;
	t_co				screen;
	t_ui				ui;
	t_co				*map_bu;
	t_process			*dead_process;
}						t_vm;

typedef struct			s_args
{
	int					aff;
	int					dump;
	int					pause;
	int					verbosity;
	int					binary;
	int					ncurse;
}						t_args;

typedef struct			s_loop
{
	int					check;
	int					last_live;
	int					death;
	char				*wait;
	int					live;
}						t_loop;

typedef struct			s_ldi
{
	int					l1;
	int					l2;
	int					p1;
	int					p2;
	int					param1;
	int					addr;
	int					reg;
}						t_ldi;

char					*ft_get_color(int player,
							t_mem *mem, t_process *process);
char					*ft_get_hex(int i, int len);
t_args					*ft_get_args(int ac, char *av[],
							t_args *args, t_vm *vm);
char					*ft_get_bin(int fd, int *size,
							char *champ, t_player *player);
void					ft_print_usage(int ac);
int						ft_print_mem(t_vm *vm);
void					ft_print_process(t_process *process);
t_player				*ft_new_player(int j, int fd, char *champ, int place);
t_mem					*ft_memnew(t_mem *prev, char byte, int color, int addr);
t_process				*ft_new_process(t_process **first, int nb, t_mem *mem);
t_args					*ft_init_args(t_args *args, int *i);
t_vm					*ft_init_vm(t_vm *vm);
t_mem					*ft_init_vm_mem(t_vm *vm);
t_op					**ft_init_instruction_list(void);
t_process				*ft_init_process(t_vm *vm);
int						ft_ispath(char *champion);
t_op					*ft_new_op(char opcode, void (*ft)(t_process *process,
						t_mem *mem, int verb, t_player **players), int cast);
void					ft_exec_instructions(t_process *process,
							t_op **instructions, t_vm *vm, int verbosity);
int						ft_check_ocp(t_mem *mem, int opcode);
int						ft_check_comp(t_mem *mem, char ocp, int decal);
int						get_ind_val(t_mem *start, t_mem *mem, int mod);
int						get_opsize(int nb, int dir_size);
int						get_nb_player(t_player **players);
void					ft_display_update(t_vm *vm, int *i, long *timestamp);
int						ft_free(t_vm *vm, t_args *args);

void					ft_init_ncurses(t_vm *vm);
long					get_microtime(void);
int						ft_get_center(int base_len, int target_len);
void					ft_display_end(t_vm *vm, int player);
void					ft_display_aa(char *str, int i_y, int i_x, int color1);
void					ft_display_pause(t_co screen, int mode);
void					ft_update_key(t_vm *vm);
void					ft_display_player_name(t_vm *vm, int marge);
void					ft_update_ui(t_vm *vm);
void					ft_print_ui_separator(t_vm *vm);
void					ft_display_player_live(t_vm *vm, int marge);
void					ft_key_hook(t_vm *vm, int *i, long *timestamp);
void					ft_init_display(t_vm *vm, int y, int x);
void					ft_display_process_next(t_vm *vm, t_process *process);
void					ft_display_update_next(t_vm *vm, int y, int x);
void					ft_update_ui_next(t_vm *vm);
void					ft_display_ui_title(t_vm *vm);
void					ft_delete_dead_process(t_vm *vm,
							t_process *dead_process);

int						ft_check_reg(char reg);
int						ft_check_comp(t_mem *mem, char ocp, int decal);
int						ft_check_load(t_mem *mem);
int						ft_check_store(t_mem *mem);
int						ft_check_add(t_mem *mem);
int						ft_check_load_index(t_mem *mem);
int						ft_check_store_index(t_mem *mem);
int						ft_check_aff(t_mem *mem);
int						is_invalid_magic(char *buff, char *champ);
int						is_invalid_size(int size,
							unsigned char *buff, char *champ);
int						ft_get_pc(t_process *process,
							t_op **instructions, int caze);
t_op					**ft_init_instruction_list(void);
int						ft_get_op_arg(t_mem **mem,
							int l1, t_process *process, int *p);
int						ft_get_idx_arg(t_mem **mem,
							int l1, t_process *process, int *p);
void					ft_print_reg(long *reg);
void					kill_process(t_process *tmp,
							t_process **process, int verbosity,
							t_vm *vm);
void					ft_check_process_lives(t_process **process,
							int *last_live,
						t_vm *vm, int verbosity);
int						ft_count_lives(t_process *process);
void					ft_loop(t_args *args, t_vm *vm);
void					init_loop(t_loop *loop, t_vm *vm, t_args *args);
void					ft_process_operations(t_process *process,
							t_op **instructions, t_vm *vm, int verbosity);
int						check_death(t_vm *vm, int *check,
							int *last_live, t_args *args);
void					ft_live(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_ld(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_st(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_add(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_sub(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_and(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_or(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_xor(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_zjmp(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_ldi(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_sti(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_fork(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_lld(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_lldi(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_lfork(t_process *process,
							t_mem *mem, int verb, t_player **players);
void					ft_aff(t_process *process,
							t_mem *mem, int verb, t_player **players);

#endif
