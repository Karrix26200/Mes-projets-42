/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/01 03:09:06 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 16:56:54 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"

# define START -1
# define NONE -2
# define END 0
# define NO_ANT -1

typedef struct		s_ant
{
	struct s_ant	*next;
	struct s_ant	**chd;
	char			*name;
	long			ant;
	int				hot;
	int				path;
	int				dfs;
	int				tour;
	long long		x;
	long long		y;
}					t_ant;

typedef struct		s_res
{
	int				nbr_ways;
	int				total_length;
	int				direct;
	int				**way;
}					t_res;

typedef struct		s_data
{
	struct s_ant	*start;
	struct s_ant	*end;
	struct s_ant	*ant_hill;
	struct s_ant	*ant_cpy;
	char			*final_str;
	long			nb_ant;
	struct s_res	*res;

}					t_data;

t_data				*pr_main(void);
int					pr_room_parse(t_data *d, char **line);
int					pr_tube_parse(t_data *d, char *line);
int					pr_is_valid_comment(char **line, t_data *d);

int					ft_is_number(char *str);
int					ft_count_words(char const *s, char c);
int					ft_count_letters(char const *s, char c);
char				*ft_rm_space(char *s);
t_data				*pr_free_all(t_data *d);
t_ant				*pr_clear_ant(t_ant *ant);
void				free_ant_cpy(t_ant *ant);
int					ft_strdel_ret(char **l);
int					pr_add_chd(t_ant *t1, t_ant *t2, int tlen);

int					pr_link_start(t_ant *begin);
int					pr_backtrack_heat(t_ant *begin, int tier, int target);

int					sv_main(t_data *data);
int					sv_redirect_way(t_data *data, int len, int path);
int					sv_choose_way(t_data *data, int len, int path);

int					get_min_hot(t_ant *node);
void				anthill_cpy(t_ant *src, t_ant *dest);
t_ant				*anthill_dup(t_ant *node);
void				reset_hot(t_ant *node);
int					apply_new_hot(t_data *d);

void				new_hot(t_data *data, t_res res);

int					sv_send(t_data *data, t_res res);
int					move_ant(t_ant *dest, t_ant *from, int tour);
int					link_start_end(t_data *data);

int					**get_way(t_data *data, t_res res);
void				free_tab(int ***tab, int size);

#endif
