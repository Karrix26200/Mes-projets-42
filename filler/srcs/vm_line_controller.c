/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_line_controller.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/23 01:46:30 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 02:39:10 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm_filler.h"

char		*change_color_init(char *line, int *line_length, int *i)
{
	char *fline;

	*line_length = get_line_length(line, 0);
	fline = ft_strnew(*line_length);
	*i = -1;
	return (fline);
}

void		change_line_end(char *fline, int x, int line_length, t_sq *p)
{
	ft_stradd(&fline, &x, NC);
	if (p->x1 == 0)
	{
		ft_stradd(&fline, &x, WHT2);
		ft_stradd(&fline, &x, "⎸");
		ft_stradd(&fline, &x, NC);
		ft_stradd(&fline, &x, "\n");
	}
	write(1, fline, line_length);
	ft_strdel(&fline);
}

void		change_line(int y, char **map, char *line, t_sq *p)
{
	int		i;
	int		x;
	char	*fline;
	int		line_length;

	fline = change_color_init(line, &line_length, &i);
	x = p->x1 == 0 ? sprintf(fline, "%s%4d  ⎹", WHT2, y) : 0;
	while (map[y][++i])
	{
		if (i == 0 || !(i > 0 && line[i + 4] == line[i + 3]))
		{
			if (map[y][i] == 'X')
				ft_stradd(&fline, &x, "\x1B[48;2;255;86;86m");
			else if (map[y][i] == 'x' && (p->y2 = p->y2 + 1))
				ft_stradd(&fline, &x, "\x1B[48;2;255;200;200m");
			else if (map[y][i] == 'O')
				ft_stradd(&fline, &x, "\x1B[48;2;107;255;210m");
			else if (map[y][i] == 'o' && (p->y1 = p->y1 + 1))
				ft_stradd(&fline, &x, "\x1B[48;2;200;255;200m");
			else
				ft_stradd(&fline, &x, NC);
		}
		ft_stradd(&fline, &x, "  ");
	}
	change_line_end(fline, x, line_length, p);
}

void		print_bot_screen_first_step(t_co map_s, t_player player, t_sq p)
{
	int ratio;
	int i;

	if (p.x1 == 0)
	{
		printf("\033[%d;%df", map_s.y + 7, 0);
		printf("       %s%s", "\x1B[38;2;107;255;210m", player.p1);
		i = -1;
		ratio = map_s.x * 2 - player.len1 - player.len2;
		while (++i < ratio)
			printf(" ");
		printf("%s%s", "\x1B[38;2;255;86;86m", player.p2);
	}
}

void		print_bot_screen(t_sq p, t_co map_s)
{
	int ratio;
	int i;

	printf("\033[%d;%df", map_s.y + 5, 0);
	printf("      %s ", WHT2);
	i = 1;
	while (++i < map_s.x + 2)
		printf("──");
	printf("\n      %s", "\x1B[38;2;107;255;210m");
	i = -1;
	ratio = p.y1 * (map_s.x) / (p.y1 + p.y2);
	while (++i < ratio)
		printf(" ◤");
	printf("%s", "\x1B[38;2;255;86;86m");
	i = -1;
	ratio = map_s.x - ratio;
	while (++i < ratio)
		printf(" ◥");
	printf("%s\n", NC);
}
