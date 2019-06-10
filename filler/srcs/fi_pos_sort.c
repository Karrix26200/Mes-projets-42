/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fi_pos_sort.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/23 23:59:52 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 00:59:03 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fi_filler.h"

void	apply_transform(int **map, t_co map_s)
{
	t_co c;

	c.y = -1;
	while (++(c.y) < map_s.y)
	{
		c.x = -1;
		while (++(c.x) < map_s.x)
		{
			if (map[c.y][c.x] == VIDE)
				map[c.y][c.x] = ft_put_case(map, c, map_s);
		}
	}
	c.y = map_s.y;
	while (--(c.y) >= 0)
	{
		c.x = map_s.x;
		while (--(c.x) >= 0)
			if (map[c.y][c.x] > 0 || map[c.y][c.x] == VIDE)
				map[c.y][c.x] = ft_put_case(map, c, map_s);
	}
}

int		transform_map(int **map, t_co map_s, t_sq es, t_sq ms)
{
	t_co	c;
	int		maxheat;

	maxheat = -1;
	apply_transform(map, map_s);
	c.y = es.y1 - 1;
	while (++(c.y) < es.y2)
	{
		c.x = es.x1 - 1;
		while (++(c.x) < es.x2)
			if (map[c.y][c.x] > 0 && map[c.y][c.x] > maxheat && !(c.x >= ms.x1
						&& c.y >= ms.y1 && c.x <= ms.x2 && c.x <= ms.y2))
				maxheat = map[c.y][c.x];
	}
	return (maxheat);
}

t_sq	get_es(int **map, t_co map_s)
{
	t_sq ms;
	t_co c;

	ms.x1 = -1;
	ms.y1 = -1;
	ms.x2 = -1;
	ms.y2 = -1;
	c.y = -1;
	while (++(c.y) < map_s.y)
	{
		c.x = -1;
		while (++(c.x) < map_s.x)
			if (map[c.y][c.x] == SOURCE)
			{
				if (c.x < ms.x1 + 1 || ms.x1 == -1)
					ms.x1 = c.x - 1;
				if (c.x > ms.x2 - 1 || ms.x2 == -1)
					ms.x2 = c.x + 1;
				if (c.y < ms.y1 + 1 || ms.y1 == -1)
					ms.y1 = c.y - 1;
				if (c.y > ms.y2 - 1 || ms.y2 == -1)
					ms.y2 = c.y + 1;
			}
	}
	return (ms);
}

t_sq	get_ms(int **map, t_co map_s)
{
	t_sq ms;
	t_co c;

	ms.x1 = -1;
	ms.y1 = -1;
	ms.x2 = -1;
	ms.y2 = -1;
	c.y = -1;
	while (++(c.y) < map_s.y)
	{
		c.x = -1;
		while (++(c.x) < map_s.x)
			if (map[c.y][c.x] == OBSTACLE)
			{
				if (c.x < ms.x1 || ms.x1 == -1)
					ms.x1 = c.x;
				if (c.x > ms.x2 || ms.x2 == -1)
					ms.x2 = c.x;
				if (c.y < ms.y1 || ms.y1 == -1)
					ms.y1 = c.y;
				if (c.y > ms.y2 || ms.y2 == -1)
					ms.y2 = c.y;
			}
	}
	return (ms);
}

void	found_better(int *testheat, int *heat, t_co *try_coord,
		t_co *final_coord)
{
	if ((*testheat < *heat || *heat == -1) && *testheat != -1)
	{
		final_coord->x = try_coord->x;
		final_coord->y = try_coord->y;
		*heat = *testheat;
	}
}
