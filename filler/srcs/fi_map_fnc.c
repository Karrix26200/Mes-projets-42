/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fi_map_fnc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/24 03:06:20 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 04:04:37 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fi_filler.h"

void	map_initier(int **mapl, char enemy, int linelen, char *line)
{
	int i;

	i = -1;
	*mapl = ft_memalloc(sizeof(int) * linelen);
	while (++i < linelen)
	{
		if (line[i + 4] == enemy)
			(*mapl)[i] = SOURCE;
		else if (line[i + 4] == '.')
			(*mapl)[i] = VIDE;
		else
			(*mapl)[i] = OBSTACLE;
	}
}

void	map_updater(int **mapl, char *line, char enemy, int linelen)
{
	int		i;
	char	me;

	if (*mapl == 0)
		return (map_initier(mapl, enemy, linelen, line));
	i = -1;
	me = enemy == 'O' ? 'X' : 'O';
	while (++i < linelen)
		if ((line[i + 4] == '.' && (*mapl)[i] != VIDE) ||
			(line[i + 4] == enemy && (*mapl)[i] != SOURCE) ||
			(line[i + 4] == me && (*mapl)[i] != OBSTACLE))
		{
			if (line[i + 4] == enemy)
				(*mapl)[i] = SOURCE;
			else
				(*mapl)[i] = OBSTACLE;
		}
}

int		**ft_get_imap(char **map, t_co map_s, char enemy)
{
	char	me;
	t_co	co;
	int		**imap;

	me = enemy == 'X' ? 'O' : 'X';
	co.y = -1;
	imap = ft_memalloc(sizeof(int*) * map_s.y);
	while (map[++(co.y)])
	{
		imap[co.y] = ft_memalloc(sizeof(int) * map_s.x + 1);
		co.x = -1;
		while (map[co.y][++(co.x)])
		{
			if (map[co.y][co.x] == '.')
				imap[co.y][co.x] = VIDE;
			else if (map[co.y][co.x] == enemy
					|| map[co.y][co.x] == ft_tolower(enemy))
				imap[co.y][co.x] = SOURCE;
			else
				imap[co.y][co.x] = OBSTACLE;
		}
	}
	return (imap);
}

void	clear_imap(int **map, t_co map_s)
{
	t_co c;

	c.y = -1;
	while (++(c.y) < map_s.y)
	{
		c.x = -1;
		while (++(c.x) < map_s.x)
			if (map[c.y][c.x] > 0)
				map[c.y][c.x] = VIDE;
	}
}

char	**parse_map(char *line, int **map, char enemy, t_co map_s)
{
	int		limit;
	int		i;
	char	**piece;
	t_co	piece_s;
	int		a;

	limit = 0;
	i = -1;
	while ((++i < limit || !limit) && get_next_line(0, &line, 0))
	{
		if (!limit && ft_strncmp(line, "Piece", 5) == 0 && (a = -1) == -1)
		{
			piece_s.y = ft_atoi(&line[ft_strindex(line, ' ') + 1]);
			piece_s.x = ft_atoi(ft_strrchr(line, ' ') + 1);
			limit = i + piece_s.y + 1;
			piece = ft_memalloc(sizeof(char*) * (piece_s.y + 1));
		}
		else if (!limit)
			map_updater(&map[i], line, enemy, map_s.x);
		else if (limit && (++a) > -1)
			piece[a] = ft_strsub(line, 0, piece_s.x);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (piece);
}
