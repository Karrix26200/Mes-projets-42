/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fd_main.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/06 21:47:26 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/18 11:53:51 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/header.h"

t_co		fd_dimmul(t_vector v, float format[3][3], int zoom)
{
	t_co newc;

	newc.x = (v.x * format[0][0] + v.y * format[1][0] +
		v.z * format[2][0]) * zoom;
	newc.y = (v.x * format[0][1] + v.y * format[1][1] +
		v.z * format[2][1]) * zoom;
	return (newc);
}

t_co		fd_get_middlev(t_data *d)
{
	t_co		middle;
	t_vector	newv;
	t_co		c;

	c.x = d->map_s.x / 2;
	c.y = d->map_s.y / 2;
	newv = fd_vectmul(d->map[c.y][c.x], d->rotatey, 0);
	newv = fd_vectmul(newv, d->rotatex, 0);
	newv = fd_vectmul(newv, d->rotatez, 0);
	middle = fd_dimmul(newv, d->change_dim, d->zoom);
	middle.x = d->center.x - middle.x;
	middle.y = d->center.y - middle.y;
	return (middle);
}

void		fd_matmul(t_data *d)
{
	t_co		c;
	t_vector	newv;
	t_co		middle;

	middle = fd_get_middlev(d);
	c.y = -1;
	while (++(c.y) < d->map_s.y)
	{
		c.x = -1;
		while (++(c.x) < d->map_s.x)
		{
			newv = fd_vectmul(d->map[c.y][c.x], d->rotatey, d->mul_z);
			newv = fd_vectmul(newv, d->rotatex, 0);
			newv = fd_vectmul(newv, d->rotatez, 0);
			d->map[c.y][c.x].projected = fd_dimmul(newv,
				d->change_dim, d->zoom);
			d->map[c.y][c.x].projected.x += middle.x;
			d->map[c.y][c.x].projected.y += middle.y;
			fd_can_print(c, d);
		}
	}
}

int			fd_update(int x, int y, t_data *d)
{
	if (d->key == 2)
	{
		d->angle.x += (float)(x - d->mouse.x) / 50;
		d->angle.y += (float)(y - d->mouse.y) / 50;
		d->mouse.x = x;
		d->mouse.y = y;
	}
	else if (d->key == 1)
	{
		d->center.x += (x - d->mouse.x);
		d->center.y += (y - d->mouse.y);
		d->mouse.x = x;
		d->mouse.y = y;
	}
	fd_get_rotatey((*d).rotatey, d->angle.y);
	fd_get_rotatex((*d).rotatex, d->angle.x);
	fd_get_rotatez((*d).rotatez, 0);
	ft_bzero(d->img_str, d->screen_s.x * d->screen_s.y * 4);
	fd_matmul(d);
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img_ptr, 0, 0);
	return (0);
}

int			main(int argc, char **argv)
{
	t_data	d;
	int		bpp;
	int		s_l;
	int		endian;

	d.angle.x = 1;
	d.angle.y = 1;
	d.key = -1;
	d.mul_z = 1;
	d.projection = 0;
	fd_get_change_dim(d.change_dim);
	if (!(d.map = pr_get_map(argc, argv, &(d.map_s), &d)))
	{
		ft_putstr("error\n");
		return (1);
	}
	fd_init_fdf(&d);
	d.img_str = (int *)mlx_get_data_addr(d.img_ptr, &(bpp), &(s_l), &(endian));
	fd_update(0, 0, &d);
	mlx_hook(d.win_ptr, 2, (1L << 0), fd_keyboard_press, (void *)&d);
	mlx_hook(d.win_ptr, 4, (1L << 2), fd_press, (void*)&d);
	mlx_hook(d.win_ptr, 5, (1L << 3), fd_release, (void*)&d);
	mlx_hook(d.win_ptr, 6, (0L), fd_update, (void*)&d);
	mlx_loop(d.mlx_ptr);
	return (fd_free_all(&d));
}
