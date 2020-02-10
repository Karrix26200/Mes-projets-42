/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fi_range_motor.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/24 00:03:36 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 04:01:00 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fi_filler.h"

int		ft_range(int x1, int y1, int x2, int y2)
{
	return (ft_sqrt(ft_pow(x2 - x1, 2) + ft_pow(y2 - y1, 2)));
}

int		ft_get_range_next(t_co try, char **piece, t_co enemy)
{
	t_co	c;
	int		testrange;
	int		range;

	range = -1;
	c.y = -1;
	while (piece[++(c.y)])
	{
		c.x = -1;
		while (piece[c.y][++(c.x)])
		{
			if (piece[c.y][c.x] == '*')
			{
				testrange = ft_range(try.x + c.x, try.y + c.y,
						enemy.x, enemy.y);
				if (testrange < range || range == -1)
					range = testrange;
			}
		}
	}
	return (range);
}

int		ft_get_range(t_co try, int **map, t_co map_s, char **piece)
{
	t_co	c;
	int		testrange;
	int		range;

	range = -1;
	c.y = -1;
	while (++(c.y) < map_s.y)
	{
		c.x = -1;
		while (++(c.x) < map_s.x)
		{
			if (map[c.y][c.x] == SOURCE)
			{
				testrange = ft_get_range_next(try, piece, c);
				if ((testrange < range || range == -1) && testrange != -1)
					range = testrange;
			}
		}
	}
	return (range);
}

int		pf(char **piece)
{
	int i;

	i = -1;
	while (piece[++i])
		ft_strdel(&piece[i]);
	ft_memdel((void**)&piece);
	return (1);
}
