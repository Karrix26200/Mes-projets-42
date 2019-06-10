/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   VM_main.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/16 20:44:39 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 02:39:46 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm_filler.h"

void		victory_end(int y, char *fline, int length)
{
	write(1, "\033[", 2);
	ft_putnbr(y + 1 + 4);
	write(1, ";8f", 3);
	write(1, fline, length);
	ft_strdel(&fline);
}

void		victory_motor(char **map, t_co map_s, int y)
{
	int		i;
	char	*fline;
	int		length;
	int		x;

	length = get_line_length(map[y], 1);
	fline = ft_strnew(length);
	x = 0;
	i = -1;
	while (++i < map_s.x)
	{
		if (i == 0 || !(i > 0 && map[y][i] == map[y][i - 1]))
		{
			if (map[y][i] == 'X' || map[y][i] == 'x')
				ft_stradd(&fline, &x, "\x1B[48;2;255;86;86m");
			else if (map[y][i] == 'O' || map[y][i] == 'o')
				ft_stradd(&fline, &x, "\x1B[48;2;107;255;210m");
			else
				ft_stradd(&fline, &x, NC);
		}
		ft_stradd(&fline, &x, "  ");
	}
	ft_stradd(&fline, &x, NC);
	victory_end(y, fline, length);
}

void		print_victory(char **map, char winer, t_co map_s, int loscore)
{
	int		a;
	int		y;
	char	looser;

	looser = winer == 'X' ? 'O' : 'X';
	y = -1;
	while (++y < map_s.y)
	{
		a = -1;
		while (++a < map_s.x)
			if (map[y][a] == looser || map[y][a] == ft_tolower(looser)
					|| map[y][a] == ft_tolower(winer))
			{
				if (map[y][a] == ft_tolower(winer))
					map[y][a] = winer;
				else
					map[y][a] = '.';
				usleep(1000000 / loscore);
				victory_motor(map, map_s, y);
			}
	}
}

void		do_at_end(t_sq p, char **map, t_co map_s, t_player *player)
{
	int y;

	if (p.x1 > 0)
	{
		if (p.y2 > p.y1)
			print_victory(map, 'X', map_s, p.y1);
		else
			print_victory(map, 'O', map_s, p.y2);
		printf("\033[%d;%df", map_s.y + 8, 0);
		write(1, "\033[?25h", 6);
		y = -1;
		while (++y < map_s.y)
			ft_strdel(&map[y]);
		ft_memdel((void**)&map);
		ft_strdel(&(player->p1));
		ft_strdel(&(player->p2));
	}
}

int			main(void)
{
	char		**map;
	t_player	player;
	t_sq		p;

	map = NULL;
	variable_init(&player, &p);
	motor(map, &p, player);
	return (0);
}
