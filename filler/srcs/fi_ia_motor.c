/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fi_ia_motor.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/23 23:52:12 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 00:59:05 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fi_filler.h"

int		is_posable(t_co try, int **map, char **piece, t_co map_s)
{
	int x;
	int y;
	int compteur;

	compteur = 0;
	y = -1;
	while (piece[++y])
	{
		x = -1;
		while (piece[y][++x])
		{
			if (try.y + y >= map_s.y || try.x + x >= map_s.x)
				return (0);
			else if (piece[y][x] == '*' &&
					map[try.y + y][try.x + x] == OBSTACLE)
			{
				compteur++;
				if (compteur > 1)
					return (0);
			}
			else if (piece[y][x] == '*' && map[try.y + y][try.x + x] == SOURCE)
				return (0);
		}
	}
	return (compteur == 1 ? 1 : 0);
}

void	ft_put_piece(int **map, char **piece, t_co try)
{
	t_co pco;

	pco.y = -1;
	while (piece[++(pco.y)])
	{
		pco.x = -1;
		while (piece[pco.y][++(pco.x)])
		{
			if (piece[pco.y][pco.x] == '*' &&
					map[try.y + pco.y][try.x + pco.x] == OBSTACLE)
				map[try.y + pco.y][try.x + pco.x] = PIECEH;
			else if (piece[pco.y][pco.x] == '*')
				map[try.y + pco.y][try.x + pco.x] = PIECE;
		}
	}
}

void	ft_enleve_piece(int **map, char **piece, t_co try)
{
	t_co pco;

	pco.y = -1;
	while (piece[++(pco.y)])
	{
		pco.x = -1;
		while (piece[pco.y][++(pco.x)])
		{
			if (map[try.y + pco.y][try.x + pco.x] == PIECE)
				map[try.y + pco.y][try.x + pco.x] = VIDE;
			else if (map[try.y + pco.y][try.x + pco.x] == PIECEH)
				map[try.y + pco.y][try.x + pco.x] = OBSTACLE;
		}
	}
}

int		get_piece_heat(int **map, t_co map_s, t_co c, int maxheat)
{
	int		tab[4];
	int		i;
	int		heat;

	tab[0] = c.x - 1 < 0 ? NOTHING : map[c.y][c.x - 1];
	tab[1] = c.y - 1 < 0 ? NOTHING : map[c.y - 1][c.x];
	tab[2] = c.x + 1 >= map_s.x ? NOTHING : map[c.y][c.x + 1];
	tab[3] = c.y + 1 >= map_s.y ? NOTHING : map[c.y + 1][c.x];
	i = -1;
	heat = 0;
	while (++i < 4)
	{
		if (tab[i] > 0)
			heat += tab[i];
		else
			heat += maxheat;
	}
	return (heat);
}

int		ft_put_case(int **map, t_co c, t_co map_s)
{
	int		tab[4];
	int		i;
	int		min;

	min = VIDE;
	tab[0] = c.x - 1 < 0 ? NOTHING : map[c.y][c.x - 1];
	tab[1] = c.y - 1 < 0 ? NOTHING : map[c.y - 1][c.x];
	tab[2] = c.x + 1 >= map_s.x ? NOTHING : map[c.y][c.x + 1];
	tab[3] = c.y + 1 >= map_s.y ? NOTHING : map[c.y + 1][c.x];
	i = -1;
	while (++i < 4)
	{
		if (tab[i] > 0 && (tab[i] < min || min == VIDE))
			min = tab[i];
		else if (tab[i] == OBSTACLE || tab[i] == PIECE || tab[i] == PIECEH)
			return (1);
	}
	return (min == VIDE ? VIDE : min + 1);
}
