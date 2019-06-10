/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fd_key.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 11:48:14 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/18 11:48:45 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/header.h"

int		fd_press(int key, int x, int y, t_data *d)
{
	if (d->key == -1)
	{
		d->mouse.x = x;
		d->mouse.y = y;
	}
	d->key = key;
	if (d->key == 4)
	{
		d->zoom *= 1.1;
		d->zoom += d->zoom == (unsigned int)(d->zoom * 1.1) ? 1 : 0;
		fd_update(x, y, d);
		d->key = -1;
	}
	else if (d->key == 5)
	{
		d->zoom /= 1.1;
		fd_update(x, y, d);
		d->key = -1;
	}
	return (0);
}

int		fd_free_all(t_data *d)
{
	int i;

	mlx_destroy_window(d->mlx_ptr, d->win_ptr);
	ft_memdel((void **)&(d->img_str));
	i = -1;
	while (++i < d->map_s.y)
		ft_memdel((void **)&d->map[i]);
	ft_memdel((void **)&d->map);
	return (0);
}

int		fd_keyboard_press(int key, t_data *d)
{
	if (key == 53)
		exit(fd_free_all(d));
	else if (key == 49)
	{
		d->angle.x = d->projection ? 0 : 120;
		d->angle.y = d->projection ? 0 : 120;
		d->projection = !(d->projection);
	}
	else if (key == 78)
		d->mul_z -= 0.1;
	else if (key == 69)
		d->mul_z += 0.1;
	fd_update(0, 0, d);
	return (0);
}

int		fd_release(int key, int x, int y, t_data *d)
{
	(void)key;
	(void)y;
	(void)x;
	d->key = -1;
	return (0);
}

void	fd_init_fdf(t_data *d)
{
	d->max_z = d->max_z == 0 ? 1 : d->max_z;
	d->min_z = d->min_z == 0 ? 1 : d->min_z;
	d->zoom = 25;
	d->mlx_ptr = mlx_init();
	d->screen_s.x = 1000;
	d->screen_s.y = 1000;
	d->win_ptr = mlx_new_window(d->mlx_ptr, d->screen_s.x,
			d->screen_s.y, "mlx 42");
	d->center.x = d->screen_s.x / 2;
	d->center.y = d->screen_s.y / 2;
	d->img_ptr = mlx_new_image(d->mlx_ptr, d->screen_s.x, d->screen_s.y);
}
