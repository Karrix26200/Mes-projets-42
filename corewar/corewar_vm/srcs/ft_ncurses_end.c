/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ncurses_end.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 02:43:41 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 11:44:35 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_get_ascii_art_next(char **ascii_art)
{
	ascii_art[14] = " *** -*   *-*   *-*   *- *** ";
	ascii_art[15] = "***-*  *-***-*-*";
	ascii_art[16] = " **-*  *-*  *- **-   *";
	ascii_art[17] = "***-*  *-***-*  *-*  *";
	ascii_art[18] = " ***-*- **-   *-***";
	ascii_art[19] = "*****-  *-  *-  *-  *";
	ascii_art[20] = "*   *-*   *-*   *-*   *- ***";
	ascii_art[21] = "*   *-*   *-*   *- * *-  *";
	ascii_art[22] = "*   *-* * *-* * *-* * *- * *";
	ascii_art[23] = "*   *- * *-  *- * *-*   *";
	ascii_art[24] = "*   *- * *-  *  -  *  -  *  ";
	ascii_art[25] = "****-   *-  *- *-****";
	ascii_art[26] = " *** -*   *-*   *-*   *- *** ";
	ascii_art[27] = "  *- **-  *-  *- ***";
	ascii_art[28] = " **-*  *-  *- *-****";
	ascii_art[29] = "***-   *- **-   *-***";
	ascii_art[30] = "  *- *-*  *-****-   *";
	ascii_art[31] = "****-*-***-   *-***";
	ascii_art[32] = " **-*-***-*  *- **";
	ascii_art[33] = "****-   *-  *- *- *";
	ascii_art[34] = " **-*  *- **-*  *- **-";
	ascii_art[35] = " **-*  *- ***-   *- **";
}

char	**ft_get_ascii_art(void)
{
	char **ascii_art;

	if (!(ascii_art = malloc(sizeof(char *) * 36)))
		return (NULL);
	ascii_art[0] = " ** -*  *-****-*  *-*  *";
	ascii_art[1] = "***-*  *-***-*  *-***";
	ascii_art[2] = " ***-*-*-*- ***";
	ascii_art[3] = "***-*  *-*  *-*  *-***";
	ascii_art[4] = "****-*-***-*-****";
	ascii_art[5] = "****-*-***-*-*";
	ascii_art[6] = " ***-*-* **-*  *- ***";
	ascii_art[7] = "*  *-*  *-****-*  *-*  *";
	ascii_art[8] = " ***-  * -  * -  * - ***";
	ascii_art[9] = "****-  *-  *-* *- **-";
	ascii_art[10] = "*  *-* *-**-* *-*  *";
	ascii_art[11] = "*-*-*-*-***";
	ascii_art[12] = "*   *-** **-* * *-*   *-*   *";
	ascii_art[13] = "*   *-**  *-* * *-*  **-*   *";
	ft_get_ascii_art_next(ascii_art);
	return (ascii_art);
}

void	ft_display_string(int y, int x, char *str, t_co colors)
{
	int		i;
	char	tmp;
	char	**ascii_art;

	ascii_art = ft_get_ascii_art();
	i = -1;
	while (str[++i])
	{
		if (ft_isalpha(str[i]))
		{
			tmp = ft_tolower(str[i]);
			ft_display_aa(ascii_art[tmp - 97], y, x + (i * 12), colors.x);
		}
		else if (ft_isdigit(str[i]))
		{
			tmp = str[i];
			ft_display_aa(ascii_art[tmp - 48 + 26], y, x + (i * 12), colors.x);
		}
	}
	ft_memdel((void **)&ascii_art);
}

void	ft_get_cup(t_vm *vm)
{
	char *cup;

	ft_memdel((void**)&(vm->map_bu));
	cup = ft_strfjoin(
	ft_strjoin("**********-**xxxxxx**-**xxxxxx**- ",
	"**xxxx**-  ******-    **-    **-    **-x*"),
	ft_strjoin("  **  *x-**********-  ******-    **-    **-",
	"    **-    **-  ******- *xxxxxx*- ********"));
	ft_display_aa(cup, vm->screen.y / 2 - 21,
	ft_get_center(vm->screen.x, 20), 13);
	ft_memdel((void **)&cup);
}

void	ft_display_end(t_vm *vm, int player)
{
	int		color_switch;
	t_co	colors;

	colors.x = 13;
	colors.y = 22 + player;
	clear();
	ft_get_cup(vm);
	while (getch() == -1 && (color_switch = colors.x))
	{
		ft_display_string(vm->screen.y / 2,
				ft_get_center(vm->screen.x,
					ft_strlen(vm->players[player]->name) * 12),
				vm->players[player]->name, colors);
		colors.x = colors.y;
		colors.y = color_switch;
		ft_display_string(vm->screen.y / 2 + 10,
				ft_get_center(vm->screen.x, 36), "WIN", colors);
		refresh();
		usleep(1000000 / 2);
	}
	clear();
	refresh();
	curs_set(1);
	echo();
	endwin();
}
