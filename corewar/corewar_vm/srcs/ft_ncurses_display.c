/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ncurses_display.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 02:43:17 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 12:03:19 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_display_aa(char *str, int i_y, int i_x, int color1)
{
	t_co	c;
	int		i;
	int		color;

	color = -1;
	i = -1;
	c.y = 0;
	c.x = -2;
	while (str[++i])
	{
		if (str[i] == '-' && (c.x = -2))
			c.y++;
		else if (str[i] == ' ')
		{
			if ((color != 0 || color == -1) && !(color = 0))
				attron(COLOR_PAIR(1));
			mvprintw(c.y + i_y, (c.x += 2) + i_x, "  ");
		}
		else
		{
			if ((color != 1 || color == -1) && (color = 1))
				attron(COLOR_PAIR(color1));
			mvprintw(c.y + i_y, (c.x += 2) + i_x, "  ");
		}
	}
}

void	ft_display_pause(t_co screen, int mode)
{
	char *str;
	char *reset;

	attron(COLOR_PAIR(7));
	str = mode
		? "-*-**-***-****-*****-****-***-**-*-"
		: "-** **-** **-** **-** **-** **-** **-** **-** **-** **-";
	reset = "-     -     -     -     -     -     -     -     -     -     -";
	ft_display_aa(reset, 70, screen.x - ((screen.x * 98 / 100)), 7);
	ft_display_aa(str, 70, screen.x - ((screen.x * 98 / 100)), 7);
}
