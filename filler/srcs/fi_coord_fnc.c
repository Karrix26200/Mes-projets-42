/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fi_coord_fnc.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/23 23:55:49 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 00:50:19 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fi_filler.h"

int		get_coord_init(t_sq *es, t_sq *ms, int **map, t_co map_s)
{
	int heat;

	*es = get_es(map, map_s);
	*ms = get_ms(map, map_s);
	heat = transform_map(map, map_s, *es, *ms);
	clear_imap(map, map_s);
	return (heat);
}

int		get_coord_init2(int heat, t_co *final_coord, t_co *try_coord)
{
	int maxheat;

	maxheat = heat;
	final_coord->x = -1;
	final_coord->y = -1;
	try_coord->y = -1;
	return (maxheat);
}

t_co	get_coord2(int **map, char **piece, t_co map_s)
{
	t_co	try_coord;
	t_co	final_coord;
	t_sq	es;
	t_sq	ms;
	t_sq	heat;

	heat.x1 = get_coord_init(&es, &ms, map, map_s);
	heat.y1 = get_coord_init2(heat.x1, &final_coord, &try_coord);
	while (++(try_coord.y) < map_s.y)
	{
		try_coord.x = -1;
		while (++(try_coord.x) < map_s.x)
			if (is_posable(try_coord, map, piece, map_s))
			{
				ft_put_piece(map, piece, try_coord);
				ms = get_ms(map, map_s);
				heat.y1 = transform_map(map, map_s, es, ms);
				found_better(&(heat.y1), &(heat.x1), &try_coord, &final_coord);
				clear_imap(map, map_s);
				ft_enleve_piece(map, piece, try_coord);
			}
	}
	final_coord.x = heat.x1 == heat.x2 ? -1 : final_coord.x;
	return (final_coord);
}

t_co	get_coord1(int **map, char **piece, t_co map_s, int *range)
{
	t_co	try_coord;
	int		testrange;
	t_co	final_coord;

	final_coord.x = -1;
	final_coord.y = -1;
	try_coord.y = -1;
	while (++(try_coord.y) < map_s.y)
	{
		try_coord.x = -1;
		while (++(try_coord.x) < map_s.x)
		{
			if (is_posable(try_coord, map, piece, map_s))
			{
				testrange = ft_get_range(try_coord, map, map_s, piece);
				if ((testrange < *range || *range == -1) && testrange != -1)
				{
					final_coord.x = try_coord.x;
					final_coord.y = try_coord.y;
					*range = testrange;
				}
			}
		}
	}
	return (final_coord);
}
