/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   header.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 06:03:23 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/18 11:54:48 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../minilibx_macos/mlx.h"
# include "../libft/includes/libft.h"
# include <math.h>
# include <fcntl.h>
# define RGB(r, g, b) (r) * 65536 + (g)*256 + (b)

typedef struct		s_co
{
	int				x;
	int				y;
}					t_co;

typedef struct		s_cof
{
	float			x;
	float			y;
}					t_cof;

typedef struct		s_vector
{
	t_co			projected;
	float			x;
	float			y;
	float			z;
}					t_vector;

typedef struct		s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*img_str;
	t_vector		**map;
	t_co			map_s;
	float			rotatex[3][3];
	float			rotatey[3][3];
	float			rotatez[3][3];
	float			change_dim[3][3];
	t_cof			angle;
	t_co			center;
	unsigned int	zoom;
	int				key;
	t_co			screen_s;
	t_co			mouse;
	int				min_z;
	int				max_z;
	float			mul_z;
	int				projection;
}					t_data;

typedef struct		s_rawmap
{
	int				len;
	int				*line;
	struct s_rawmap *next;
}					t_rawmap;

t_vector			**pr_get_map(int argc, char **argv, t_co *map_s, t_data *d);
int					pr_get_line_len(char *line);
int					*pr_get_line_int(char *line, int len);
int					fd_press(int key, int x, int y, t_data *d);
int					fd_keyboard_press(int key, t_data *d);
int					fd_release(int key, int x, int y, t_data *d);
int					fd_free_all(t_data *d);
void				fd_init_fdf(t_data *d);
void				fd_get_change_dim(float tab[3][3]);
void				fd_get_rotatex(float tab[3][3], float angle);
void				fd_get_rotatey(float tab[3][3], float angle);
void				fd_get_rotatez(float tab[3][3], float angle);
t_vector			fd_vectmul(t_vector v, float format[3][3], float mul_z);
void				fd_can_print(t_co c, t_data *d);
int					fd_update(int x, int y, t_data *d);

#endif
