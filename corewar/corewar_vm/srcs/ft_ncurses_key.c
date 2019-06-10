/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ncurses_key.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 02:44:10 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/18 02:44:12 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_update_key(t_vm *vm)
{
	attron(COLOR_PAIR(8) | A_BOLD);
	mvprintw(72, vm->ui.line_marge +
			ft_get_center(vm->ui.line_len / 3, 13) - 3 * 2, " < ");
	mvprintw(72, vm->ui.line_marge +
			ft_get_center(vm->ui.line_len / 3, 13) - 3 * 4, "<< ");
	mvprintw(72, vm->ui.line_marge +
			ft_get_center(vm->ui.line_len / 3, 13) + 11 + 3 * 2, " > ");
	mvprintw(72, vm->ui.line_marge +
			ft_get_center(vm->ui.line_len / 3, 13) + 11 + 3 * 4, " >>");
	attron(COLOR_PAIR(9));
	mvprintw(71, vm->ui.line_marge +
			ft_get_center(vm->ui.line_len / 3, 13) - 3 * 2, " W ");
	mvprintw(71, vm->ui.line_marge +
			ft_get_center(vm->ui.line_len / 3, 13) - 3 * 4, " Q ");
	mvprintw(71, vm->ui.line_marge +
			ft_get_center(vm->ui.line_len / 3, 13) + 11 + 3 * 4, " R ");
	mvprintw(71, vm->ui.line_marge +
			ft_get_center(vm->ui.line_len / 3, 13) + 11 + 3 * 2, " E ");
}

void	ft_key_down_next(t_vm *vm, int c)
{
	if (c == 'w')
		mvprintw(71, vm->ui.line_marge +
				ft_get_center(vm->ui.line_len / 3, 13) - 3 * 2, " W ");
	else if (c == 'q')
		mvprintw(71, vm->ui.line_marge +
				ft_get_center(vm->ui.line_len / 3, 13) - 3 * 4, " Q ");
	else if (c == 'r')
		mvprintw(71, vm->ui.line_marge +
				ft_get_center(vm->ui.line_len / 3, 13) + 11 + 3 * 4, " R ");
	else if (c == 'e')
		mvprintw(71, vm->ui.line_marge +
				ft_get_center(vm->ui.line_len / 3, 13) + 11 + 3 * 2, " E ");
	attron(COLOR_PAIR(6));
	if (c == 'w')
		mvprintw(72, vm->ui.line_marge +
				ft_get_center(vm->ui.line_len / 3, 13) - 3 * 2, " < ");
	else if (c == 'q')
		mvprintw(72, vm->ui.line_marge +
				ft_get_center(vm->ui.line_len / 3, 13) - 3 * 4, "<< ");
	else if (c == 'r')
		mvprintw(72, vm->ui.line_marge +
				ft_get_center(vm->ui.line_len / 3, 13) + 11 + 3 * 4, " >>");
	else if (c == 'e')
		mvprintw(72, vm->ui.line_marge +
				ft_get_center(vm->ui.line_len / 3, 13) + 11 + 3 * 2, " > ");
}

void	ft_key_down(t_vm *vm, char c)
{
	static long		key_time;
	static char		last_key;
	static int		wait;

	if (c == 'w' || c == 'q' || c == 'r' || c == 'e')
	{
		if (last_key != c && (wait = 275000))
			ft_update_key(vm);
		else
			wait = 50000;
		last_key = c;
		key_time = get_microtime();
		attron(COLOR_PAIR(10) | A_BOLD);
		ft_key_down_next(vm, c);
	}
	else if (key_time != 0 && key_time + wait < get_microtime())
	{
		last_key = 0;
		key_time = 0;
		ft_update_key(vm);
	}
}

void	ft_key_hook_next(t_vm *vm, int c)
{
	if (c == ' ')
		vm->ui.pause = (vm->ui.pause == 1) ? 0 : 1;
	else if (c == 's')
	{
		vm->ui.pause = 1;
		vm->ui.tpt = 1;
	}
	else if (c == 'r' && vm->ui.speed + 10 > 1000)
		vm->ui.speed = 1000;
	else if (c == 'r')
		vm->ui.speed += 10;
	else if (c == 'e' && vm->ui.speed + 1 > 1000)
		vm->ui.speed = 1000;
	else if (c == 'e')
		vm->ui.speed += 1;
	else if (c == 'w' && vm->ui.speed - 1 < 1)
		vm->ui.speed = 1;
	else if (c == 'w')
		vm->ui.speed -= 1;
	else if (c == 'q' && vm->ui.speed - 10 < 1)
		vm->ui.speed = 1;
	else if (c == 'q')
		vm->ui.speed -= 10;
}

void	ft_key_hook(t_vm *vm, int *i, long *timestamp)
{
	int		c;
	int		pause_tmp;

	vm->ui.tpt = 0;
	pause_tmp = vm->ui.pause;
	c = getch();
	ft_key_hook_next(vm, c);
	if ((c == 'r' || c == 'e' || c == 'w' || c == 'q') && (*i = 1))
		*timestamp = get_microtime();
	ft_key_down(vm, c);
	if (pause_tmp != vm->ui.pause)
		ft_display_pause(vm->screen, vm->ui.pause);
}
