/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ncurses_next.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 02:44:24 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 11:30:33 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_display_process_next(t_vm *vm, t_process *process)
{
	int x;
	int y;

	y = process->mem_bu->addr / 64;
	x = process->mem_bu->addr % 64;
	attron(COLOR_PAIR(process->mem_bu->player + 32));
	if (process->mem_bu->player != -1)
		mvprintw(y, (x * 4) + ((vm->screen.x - (64 * 4)) / 2),
				" %.2X ", process->mem_bu->byte);
	else
	{
		attron(COLOR_PAIR(1));
		mvprintw(y, (x * 4) + ((vm->screen.x - (64 * 4)) / 2),
				"    ");
	}
}

void	ft_display_update_next(t_vm *vm, int y, int x)
{
	while (++y < 64)
	{
		x = -1;
		while (++x < 64)
		{
			if (vm->mem->byte != vm->map_bu[y * 64 + x].x ||
					vm->mem->player != vm->map_bu[y * 64 + x].y)
			{
				vm->map_bu[y * 64 + x].x = vm->mem->byte;
				vm->map_bu[y * 64 + x].y = vm->mem->player;
				vm->mem->update_color = vm->ui.speed + 1;
				attron(COLOR_PAIR(vm->mem->player + 32));
				mvprintw(y, (x * 4) + ((vm->screen.x - (64 * 4)) / 2),
						" %.2X ", vm->mem->byte);
			}
			else if (vm->mem->update_color &&
					!(vm->mem->update_color -= !vm->ui.pause))
			{
				attron(COLOR_PAIR(vm->mem->player + 2));
				mvprintw(y, (x * 4) + ((vm->screen.x - (64 * 4)) / 2),
						" %.2X ", vm->mem->byte);
			}
			vm->mem = vm->mem->next;
		}
	}
}

void	ft_update_ui_next(t_vm *vm)
{
	char *speed;

	speed = ft_itoa(vm->ui.speed);
	mvprintw(72, vm->ui.line_marge +
			ft_get_center(vm->ui.line_len / 3,
				ft_strlen("                ")), "                ");
	mvprintw(72, vm->ui.line_marge + ft_get_center(vm->ui.line_len / 3,
				ft_strlen(speed)), "%s", speed);
	mvprintw(75, vm->ui.line_marge + ft_get_center(vm->ui.line_len / 3,
				ft_strlen("                ")), "                ");
	ft_memdel((void **)&speed);
}

void	ft_display_ui_title(t_vm *vm)
{
	mvprintw(77, vm->ui.line_marge +
			ft_get_center(vm->ui.line_len / 3, 9), "Processes");
	mvprintw(69, vm->ui.line_marge + vm->ui.line_len / 3 * 2 +
			ft_get_center(vm->ui.line_len / 3, 12), "Cycle to die");
	mvprintw(72, vm->ui.line_marge + vm->ui.line_len / 3 * 2 +
			ft_get_center(vm->ui.line_len / 3, 11), "Cycle delta");
	mvprintw(75, vm->ui.line_marge + vm->ui.line_len / 3 * 2 +
			ft_get_center(vm->ui.line_len / 3, 8), "Nbr live");
	mvprintw(78, vm->ui.line_marge + vm->ui.line_len / 3 * 2 +
			ft_get_center(vm->ui.line_len / 3, 9), "Max check");
}

void	ft_delete_dead_process(t_vm *vm, t_process *dead_process)
{
	t_process	*tmp;
	t_co		c;

	while (dead_process)
	{
		if (dead_process->mem_bu)
		{
			c.y = dead_process->mem_bu->addr / 64;
			c.x = dead_process->mem_bu->addr % 64;
			attron(COLOR_PAIR(dead_process->mem_bu->player + 32));
			if (dead_process->mem_bu->player != -1)
				mvprintw(c.y, (c.x * 4) + ((vm->screen.x - (64 * 4)) / 2),
						" %.2X ", dead_process->mem_bu->byte);
			else
			{
				attron(COLOR_PAIR(1));
				mvprintw(c.y, (c.x * 4) + ((vm->screen.x - (64 * 4)) / 2),
						"    ");
			}
		}
		tmp = dead_process;
		dead_process = dead_process->next;
		ft_memdel((void**)&tmp->reg);
		ft_memdel((void**)&tmp);
	}
}
