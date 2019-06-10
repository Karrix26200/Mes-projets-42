/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/10 22:18:48 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 11:58:25 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../../libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>
# define WPRM "Wrong parameters at instruction "
# define WARG "Wrong number of arguments at instruction "
# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3
# define MAX_ARGS_NUMBER			4
# define MAX_PLAYERS				4
# define MEM_SIZE				(4*1024)
# define IDX_MOD					(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR				'%'
# define SEPARATOR_CHAR			','
# define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING			".name"
# define COMMENT_CMD_STRING		".comment"
# define REG_NUMBER				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA				50
# define NBR_LIVE				21
# define MAX_CHECKS				10
# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef char		t_arg_type;

typedef struct		s_header
{
	unsigned int	magic;
	char			*prog_name;
	unsigned int	prog_size;
	char			*comment;
}					t_header;

typedef struct		s_id
{
	char			*name;
	char			*comment;
	unsigned int	prog_size;
}					t_id;

typedef	struct		s_asm
{
	char			*label;
	char			*instruction;
	char			opcode;
	char			param_code;
	char			**params;
	struct s_asm	*next;
	size_t			size;
}					t_asm;

typedef struct		s_data
{
	char			*line;
	char			*file;
	int				fd;
	int				nb;
	int				option;
}					t_data;

char				**ft_init_instruction_list(void);
int					ft_get_instruction(t_asm **assemb,
						t_data *data, unsigned int *prog_size);
int					is_valid_instruction(char *line);
int					ft_check_labels(t_asm *assemb, t_asm *first);
void				*free_id(t_header *id);
void				*free_instr(t_asm *instr);
char				**free_tab(char **tab);
void				*free_instr(t_asm *instr);
int					free_lst(t_asm **instr, char **lst);
int					clean_exit(int error, t_data *data,
						t_asm *assemb, t_header *id);
t_header			*get_champ_id(int fd, char **line, int *nb);
int					check_missing_cmd(char **line,
						int res, t_header *id, int *nb);
char				*check_length(int type, char *comm);
int					is_skipable(char *line, int nb);
int					get_param_nb(char **params);
int					is_direct(char *str);
int					is_indirect(char *str);
int					is_registre(char *str);
int					wrong_nb_param(int opcode, char **params);
int					is_wrong_instr(char *instr,
						char **params, int opcode, int l);
int					is_invalidparam(char *param);
char				**split_params(char *line);
int					check_param(char **params, int i, int j);
char				**get_params(char *line);
void				add_label(t_asm *instr,
						t_data *data, int *tmp, int *i);
int					add_instr_val(t_asm *instr, t_data *data, int *i);
int					check_instruction(t_asm *instr, t_data *data,
						char **i_lst, unsigned int *prog_size);
int					check_unexpected_cmd(t_data *data, char **i_lst);
int					ft_putreg(char *param, t_data *data);
int					ft_putadd(char *label,
						t_asm *assemb, t_asm *position, t_data *data);
int					ft_putdir(char *param,
						t_asm *assemb, t_asm *position, t_data *data);
int					ft_putind(char *param,
						t_asm *assemb, t_asm *position, t_data *data);
int					match_label(char *haystack, char *needle, int index);
size_t				ft_find_label(t_asm *assemb,
						t_asm *position, int *check, char *label);
void				ft_write_dir(char *param,
						int fd, int dir_size, int option);
void				ft_write_else(char *param, int fd, int option);
void				write_neg_ind(int ind, t_data *data);
int					ft_putname(char *name, int fd);
int					ft_putcomment(char *name, int size, int fd);
void				ft_display_id(t_data *data, t_header *id, int *bit);
void				ft_print_option(t_asm *list, int *bit);
void				ft_write_addr_option(t_asm *list,
						t_asm *assemb, int i, int *check);
void				ft_write_synth_option(t_asm *list, t_asm *assemb);
void				ft_option_pres(char *name, char *comm, int size);
void				print_argument(t_asm *tmp, t_data *data, t_asm *assemb);
void				ft_print_label(char *label, int bit);
void				ft_write_params(t_asm *assemb_tmp,
						t_asm *assemb, t_data *data);
int					ft_create_bin(t_asm *assemb, t_header *id,
						char *name, t_data *data);
char				get_param_code(char **params, size_t *size,
						int opcode, unsigned int *prog_size);
char				get_opcode(char *instr, char **i_lst);
char				**check_label_chars(char *label, int *j);

#endif
