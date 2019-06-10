/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_motor.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/23 01:52:09 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 02:45:33 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm_filler.h"

void		teleport_to_line(int *testbool, int y, int tour)
{
	if (tour != 0 && *testbool == 0)
	{
		write(1, "\033[", 2);
		ft_putnbr(y + 1 + 4);
		write(1, tour == 0 ? ";0f" : ";8f", 3);
		*testbool = 1;
	}
}

void		variable_init(t_player *player, t_sq *p)
{
	p->x1 = -1;
	write(1, CLEAR_S, 10);
	write(1, "\033[H", 3);
	write(1, "\033[?25l", 6);
	player->p1 = ft_get_player(NULL);
	player->p2 = ft_get_player(NULL);
	player->len1 = ft_strlen(player->p1);
	player->len2 = ft_strlen(player->p2);
}

void		change_detector(char **map, t_co map_s, t_sq *p)
{
	int		x;
	char	*line;
	int		testbool;
	int		y;

	y = -1;
	line = NULL;
	while (++y < map_s.y)
	{
		testbool = 0;
		get_next_line(0, &line, 0);
		x = -1;
		while (++x < map_s.x)
			if (map[y][x] != line[x + 4])
			{
				if (map[y][x] != 'o' && map[y][x] != 'x')
					map[y][x] = ft_tolower(line[x + 4]);
				else
					map[y][x] = line[x + 4];
				teleport_to_line(&testbool, y, p->x1);
			}
		if (p->x1 == 0 || (testbool && (testbool = !testbool) == 0))
			change_line(y, map, line, p);
		ft_strdel(&line);
	}
}

char		**init_data(t_co *map_s, char *line, int *scoreo, int *scorex)
{
	int		i;
	int		y;
	char	**map;

	map_s->y = ft_atoi(ft_strchr(line, ' ') + 1);
	map_s->x = ft_atoi(ft_strrchr(line, ' ') + 1);
	*scoreo = 0;
	*scorex = 0;
	map = ft_memalloc(sizeof(map) * map_s->y);
	y = -1;
	while (++y < map_s->y)
		map[y] = ft_memalloc(sizeof(char) * (map_s->x + 1));
	printf("\n        %s", WHT2);
	i = -1;
	while (++i < map_s->x)
		printf("%d ", i % 10);
	printf("\n\n");
	printf("       ");
	i = 1;
	while (++i < map_s->x + 2)
		printf("──");
	printf("%s\n", NC);
	return (map);
}

void		motor(char **map, t_sq *p, t_player player)
{
	long	lagtime;
	char	*line;
	t_co	map_s;

	map_s.x = -1;
	while (get_next_line(0, &line, 0) == 1)
	{
		if (ft_strncmp(line, "Pla", 3) == 0 && ++(p->x1) >= 0)
		{
			lagtime = get_microtime();
			if (p->x1 == 0)
				map = init_data(&map_s, line, &(p->y1), &(p->y2));
			ft_strdel(&line);
			get_next_line(0, &line, 0);
			change_detector(map, map_s, p);
			sleep_calculator(lagtime);
			print_bot_screen(*p, map_s);
			print_bot_screen_first_step(map_s, player, *p);
		}
		ft_strdel(&line);
	}
	do_at_end(*p, map, map_s, &player);
}
