/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ncurses_update.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 02:44:24 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 12:03:02 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_update_ui(t_vm *vm)
{
	int		marge;
	char	*nbr;

	marge = vm->ui.line_marge + vm->ui.line_len / 3;
	attron(COLOR_PAIR(6) | A_NORMAL);
	ft_update_ui_next(vm);
	nbr = ft_itoa(vm->cycle);
	mvprintw(75, vm->ui.line_marge + ft_get_center(vm->ui.line_len / 3,
				ft_strlen(nbr)), "%d", vm->cycle);
	ft_memdel((void **)&nbr);
	mvprintw(78, vm->ui.line_marge + ft_get_center(vm->ui.line_len / 3,
				ft_strlen("                ")), "                ");
	nbr = ft_itoa(vm->process->nb);
	mvprintw(78, vm->ui.line_marge + ft_get_center(vm->ui.line_len / 3,
				ft_strlen(nbr)), "%d", vm->process->nb);
	ft_memdel((void**)&nbr);
	nbr = ft_itoa(vm->death);
	mvprintw(70, vm->ui.line_marge + vm->ui.line_len / 3 * 2 +
	ft_get_center(vm->ui.line_len / 3, ft_strlen(nbr)), "%d",
	vm->death);
	ft_memdel((void**)&nbr);
}

void	ft_display_process(t_vm *vm, t_process *process)
{
	int x;
	int y;

	ft_delete_dead_process(vm, vm->dead_process);
	vm->dead_process = NULL;
	while (process)
	{
		if (process->mem_bu)
			ft_display_process_next(vm, process);
		y = process->mem->addr / 64;
		x = process->mem->addr % 64;
		attron(COLOR_PAIR(process->mem->player + 22));
		if (process->mem->player != -1)
			mvprintw(y, (x * 4) + ((vm->screen.x - (64 * 4)) / 2),
			" %.2X ", process->mem->byte);
		else
		{
			attron(COLOR_PAIR(7));
			mvprintw(y, (x * 4) + ((vm->screen.x - (64 * 4)) / 2),
			"    ");
		}
		process->mem_bu = process->mem;
		process = process->next;
	}
}

void	ft_display_update(t_vm *vm, int *i, long *timestamp)
{
	if (!vm || !vm->process)
		return ;
	ft_key_hook(vm, i, timestamp);
	ft_update_ui(vm);
	ft_display_update_next(vm, -1, -1);
	ft_display_process(vm, vm->process);
	refresh();
}

void	ft_print_ui_separator(t_vm *vm)
{
	int		i;
	t_co	marge;
	int		marge2;
	char	*tmp;

	attron(COLOR_PAIR(6));
	marge.x = vm->screen.x - ((vm->screen.x * 2 / 3));
	marge.y = vm->screen.x - ((vm->screen.x * 1 / 3));
	i = 65;
	while (++i < vm->screen.y)
	{
		mvprintw(i, marge.x, "⎸");
		mvprintw(i, marge.y, "⎸");
	}
	marge2 = vm->ui.line_marge + vm->ui.line_len / 3;
	ft_display_aa((tmp = ft_strjoin("x   x     -x   x ****-x   x*    - x ",
				"x  *** -  x      *-     **** -")),
			72, marge2 + ft_get_center(vm->ui.line_len / 3, 16), 7);
	ft_memdel((void**)&tmp);
}

void	ft_display_player_name(t_vm *vm, int marge)
{
	if (vm->players[0])
	{
		attron(COLOR_PAIR(2) | A_NORMAL);
		mvprintw(71, marge + ft_get_center(vm->ui.line_len / 3 / 2,
			ft_strlen(vm->players[0]->name)), "%s", vm->players[0]->name);
	}
	if (vm->players[1])
	{
		attron(COLOR_PAIR(3));
		mvprintw(71, marge + ft_get_center(vm->ui.line_len / 2,
			ft_strlen(vm->players[1]->name)), "%s", vm->players[1]->name);
	}
	if (vm->players[2])
	{
		attron(COLOR_PAIR(4));
		mvprintw(77, marge + ft_get_center(vm->ui.line_len / 3 / 2,
			ft_strlen(vm->players[2]->name)), "%s", vm->players[2]->name);
	}
	if (vm->players[3])
	{
		attron(COLOR_PAIR(5));
		mvprintw(77, marge + ft_get_center(vm->ui.line_len / 2,
			ft_strlen(vm->players[3]->name)), "%s", vm->players[3]->name);
	}
}
