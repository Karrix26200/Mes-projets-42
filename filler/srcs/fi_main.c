/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fi_main.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/24 01:04:02 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 04:03:41 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fi_filler.h"

void	print_res(int y, int x)
{
	char *str;

	str = ft_strjoin_del(ft_itoa(y), ft_strdup(" "));
	str = ft_strjoin_del(str, ft_itoa(x));
	str = ft_strjoin_del(str, ft_strdup("\n"));
	write(1, str, ft_strlen(str));
	ft_strdel(&str);
}

int		tracker2(int **map, char **piece, t_co map_s)
{
	t_co	toprint;
	int		range;

	range = -1;
	toprint = get_coord2(map, piece, map_s);
	if (toprint.x == -1)
	{
		toprint = get_coord1(map, piece, map_s, &range);
		if (toprint.x == -1)
		{
			print_res(0, 0);
			return (1);
		}
	}
	print_res(toprint.y, toprint.x);
	return (0);
}

int		final_free(int **map)
{
	int i;

	i = -1;
	while (map[++i])
		ft_memdel((void**)&(map)[i]);
	ft_memdel((void**)&map);
	return (0);
}

int		**filler_init(t_co *map_s, char *enemy)
{
	int		**map;
	char	*line;

	get_next_line(0, &line, 0);
	*enemy = ft_atoi(&line[ft_strindex(line, 'p') + 1]) == 1 ? 'X' : 'O';
	ft_strdel(&line);
	get_next_line(0, &line, 0);
	map_s->y = ft_atoi(ft_strchr(line, ' ') + 1);
	map_s->x = ft_atoi(ft_strrchr(line, ' ') + 1);
	ft_strdel(&line);
	map = ft_memalloc(sizeof(char*) * (map_s->y + 1));
	map[map_s->y] = 0;
	return (map);
}

int		main(void)
{
	char	*line;
	char	enemy;
	int		**map;
	t_co	map_s;
	char	**piece;

	map = filler_init(&map_s, &enemy);
	while (1)
	{
		if (map[0] != 0 && get_next_line(0, &line, 0))
		{
			if (ft_strindex(line, '=') != -1)
			{
				ft_strdel(&line);
				get_next_line(0, &line, 0);
			}
			ft_strdel(&line);
		}
		get_next_line(0, &line, 0);
		piece = parse_map(line, map, enemy, map_s);
		ft_strdel(&line);
		if ((tracker2(map, piece, map_s) && pf(piece)) || !pf(piece))
			break ;
	}
	return (final_free(map));
}
