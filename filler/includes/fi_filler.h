/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fi_filler.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/24 01:09:53 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 04:01:14 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FI_FILLER_H
# define FI_FILLER_H

# define SOURCE -2
# define OBSTACLE -3
# define VIDE -4
# define PIECE -5
# define PIECEH -6
# define NOTHING -7

# include "../libft/includes/libft.h"

typedef struct	s_co
{
	int			x;
	int			y;
}				t_co;

typedef struct	s_sq
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
}				t_sq;

t_co			get_coord2(int **map, char **piece, t_co map_s);
t_co			get_coord1(int **map, char **piece, t_co map_s, int *range);
t_sq			get_es(int **map, t_co map_s);
t_sq			get_ms(int **map, t_co map_s);
void			clear_imap(int **map, t_co map_s);
char			**parse_map(char *line, int **map, char enemy, t_co map_s);
int				transform_map(int **map, t_co map_s, t_sq es, t_sq ms);
int				is_posable(t_co trye, int **map, char **piece, t_co map_s);
void			ft_put_piece(int **map, char **piece, t_co trye);
void			ft_enleve_piece(int **map, char **piece, t_co trye);
int				ft_get_range(t_co trye, int **map, t_co map_s, char **piece);
void			found_better(int *testheat, int *heat, t_co *try_coord,
		t_co *final_coord);
int				ft_put_case(int **map, t_co c, t_co map_s);
int				pf(char **piece);

#endif
