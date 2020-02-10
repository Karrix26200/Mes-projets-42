/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fd_display.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 11:46:53 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/18 11:51:49 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/header.h"

int			ft_abs(int nbr)
{
	return (nbr < 0 ? nbr * -1 : nbr);
}

void		fill_pixel(t_data *d, int x, int y, int color)
{
	if (y >= 0 && y < d->screen_s.y && x >= 0 && x < d->screen_s.x &&
			d->img_str[(y * d->screen_s.x + x)] == 0)
		d->img_str[(y * d->screen_s.x + x)] = color;
}

void		draw_line(t_data *d, t_co src, t_co dst, int color)
{
	t_cof	step;
	int		n;
	int		i;

	i = -1;
	step.x = dst.x - src.x;
	step.y = dst.y - src.y;
	if (ft_abs(step.x) > ft_abs(step.y))
	{
		n = ft_abs(step.x);
		step.y /= ft_abs(step.x);
		step.x /= ft_abs(step.x);
	}
	else
	{
		n = ft_abs(step.y);
		step.x /= ft_abs(step.y);
		step.y /= ft_abs(step.y);
	}
	while (++i < n)
		fill_pixel(d, src.x + i * step.x, src.y + i * step.y, color);
}

int			fd_get_color(int z, t_data *d)
{
	if (z < 0)
		return (RGB(0, 199 - (154 * z / d->min_z), 230 - (154 * z / d->min_z)));
	return (RGB((254 * z / d->max_z), 177 - (99 * z / d->max_z),
				(99 * z / d->max_z)));
}

void		fd_can_print(t_co c, t_data *d)
{
	if (c.x > 0 && ((d->map[c.y][c.x - 1].projected.x >= 0 &&
		d->map[c.y][c.x - 1].projected.x < d->screen_s.x) ||
		(d->map[c.y][c.x].projected.x >= 0 &&
		d->map[c.y][c.x].projected.x < d->screen_s.x)))
		draw_line(d, d->map[c.y][c.x].projected,
			d->map[c.y][c.x - 1].projected,
			fd_get_color(d->map[c.y][c.x].z, d));
	if (c.y > 0 && ((d->map[c.y - 1][c.x].projected.y >= 0 &&
		d->map[c.y - 1][c.x].projected.y < d->screen_s.y) ||
		(d->map[c.y][c.x].projected.x >= 0 &&
		d->map[c.y][c.x].projected.x < d->screen_s.x)))
		draw_line(d, d->map[c.y][c.x].projected,
			d->map[c.y - 1][c.x].projected,
			fd_get_color(d->map[c.y][c.x].z, d));
}
