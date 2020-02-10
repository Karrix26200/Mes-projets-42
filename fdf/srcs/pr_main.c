/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fd_map_parser.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/03 01:27:44 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/18 09:57:41 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/header.h"

void			pr_get_map_elem(t_vector **map, t_rawmap *rawmap, t_data *d,
	t_co c)
{
	map[c.y][c.x].z = rawmap->line[c.x];
	if (map[c.y][c.x].z < d->min_z)
		d->min_z = map[c.y][c.x].z;
	if (map[c.y][c.x].z > d->max_z)
		d->max_z = map[c.y][c.x].z;
	map[c.y][c.x].y = c.y;
	map[c.y][c.x].x = c.x;
}

t_vector		**pr_get_varray(t_rawmap *rawmap, int linelen, int height,
		t_data *d)
{
	t_vector	**map;
	t_co		c;
	t_rawmap	*tmp;

	if (!(linelen > 0 && height > 0))
		return (NULL);
	tmp = rawmap;
	rawmap = rawmap->next;
	ft_memdel((void**)&tmp);
	c.y = -1;
	map = (t_vector**)malloc(sizeof(t_vector*) * height);
	while (rawmap)
	{
		c.x = -1;
		map[++c.y] = (t_vector*)malloc(sizeof(t_vector) * linelen);
		while (++c.x < rawmap->len)
			pr_get_map_elem(map, rawmap, d, c);
		tmp = rawmap;
		rawmap = rawmap->next;
		ft_memdel((void**)&tmp);
	}
	return (map);
}

t_rawmap		*pr_parse_line(char *line, int *len, int *bulen)
{
	t_rawmap	*rawmap;

	if (!(rawmap = ft_memalloc(sizeof(*rawmap))) ||
			!(rawmap->len = pr_get_line_len(line)) ||
			!(*bulen == -1 || rawmap->len == *bulen) ||
			!(rawmap->line = pr_get_line_int(line, rawmap->len)))
		return (NULL);
	*bulen = *bulen == -1 ? rawmap->len : *bulen;
	*len = *len + rawmap->len;
	return (rawmap);
}

t_rawmap		*pr_init_var(char **line, t_rawmap **rawmap, t_co *fd_pts_nbr,
	t_co *hei_bu_len)
{
	if (!(*rawmap = ft_memalloc(sizeof(**rawmap))))
		return (NULL);
	fd_pts_nbr->y = 0;
	hei_bu_len->x = 0;
	*line = NULL;
	hei_bu_len->y = -1;
	return (*rawmap);
}

t_vector		**pr_get_map(int argc, char **argv, t_co *map_s, t_data *d)
{
	char		*line;
	t_rawmap	*rawmap;
	t_rawmap	*begin;
	t_co		fd_pts_nbr;
	t_co		hei_bu_len;

	if (argc == 2 && (fd_pts_nbr.x = open(argv[1], O_RDONLY)) == 3)
	{
		begin = pr_init_var(&line, &rawmap, &fd_pts_nbr, &hei_bu_len);
		while (get_next_line(fd_pts_nbr.x, &line, 0) == 1 && line != NULL)
		{
			if (!(rawmap->next = pr_parse_line(line, &fd_pts_nbr.y,
				&hei_bu_len.y)))
				return (NULL);
			rawmap = rawmap->next;
			ft_strdel(&line);
			hei_bu_len.x++;
		}
		ft_strdel(&line);
		map_s->x = hei_bu_len.y;
		map_s->y = hei_bu_len.x;
		return (pr_get_varray(begin, hei_bu_len.y, hei_bu_len.x, d));
	}
	return (NULL);
}
