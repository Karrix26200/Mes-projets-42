/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ncurses_main.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 02:44:16 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 11:56:04 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_display_ui_next(t_vm *vm)
{
	char *tmp;

	ft_display_ui_title(vm);
	attron(COLOR_PAIR(6));
	tmp = ft_itoa(CYCLE_TO_DIE);
	mvprintw(70, vm->ui.line_marge + vm->ui.line_len / 3 * 2 +
			ft_get_center(vm->ui.line_len / 3,
				ft_strlen(tmp)), "%d", CYCLE_TO_DIE);
	ft_memdel((void**)&tmp);
	tmp = ft_itoa(CYCLE_DELTA);
	mvprintw(73, vm->ui.line_marge + vm->ui.line_len / 3 * 2 +
			ft_get_center(vm->ui.line_len / 3,
				ft_strlen(tmp)), "%d", CYCLE_DELTA);
	ft_memdel((void **)&tmp);
	tmp = ft_itoa(NBR_LIVE);
	mvprintw(76, vm->ui.line_marge + vm->ui.line_len / 3 * 2 +
			ft_get_center(vm->ui.line_len / 3,
				ft_strlen(tmp)), "%d", NBR_LIVE);
	ft_memdel((void **)&tmp);
	tmp = ft_itoa(MAX_CHECKS);
	mvprintw(79, vm->ui.line_marge + vm->ui.line_len / 3 * 2 +
			ft_get_center(vm->ui.line_len / 3,
				ft_strlen(tmp)), "%d", MAX_CHECKS);
	ft_memdel((void**)&tmp);
}

void	ft_display_ui(t_vm *vm)
{
	int		marge;
	int		i;

	ft_display_pause(vm->screen, 1);
	i = -1;
	attron(COLOR_PAIR(6));
	while (++i < vm->ui.line_len)
		mvprintw(65, i + (vm->screen.x - vm->ui.line_len) / 2, "─");
	attron(COLOR_PAIR(8) | A_BOLD);
	mvprintw(71, vm->ui.line_marge + ft_get_center(vm->ui.line_len / 3, 13),
			"Cycles/Second");
	mvprintw(74, vm->ui.line_marge + ft_get_center(vm->ui.line_len / 3, 6),
			"Cycles");
	ft_display_ui_next(vm);
	ft_update_key(vm);
	marge = vm->ui.line_marge + vm->ui.line_len / 3;
	ft_display_player_name(vm, marge);
	ft_update_ui(vm);
	ft_print_ui_separator(vm);
}

void	ft_init_map_bu(t_vm *vm)
{
	t_mem	*tmp;
	int		i;

	if (!(vm->map_bu = malloc(sizeof(t_co) * (64 * 64))))
		return ;
	tmp = vm->mem;
	i = -1;
	while (++i < 4096)
	{
		vm->map_bu[i].x = tmp->byte;
		vm->map_bu[i].y = tmp->player;
		tmp->update_color = 0;
		tmp = tmp->next;
	}
}

void	ft_init_color(void)
{
	init_pair(1, 232, COLOR_BLACK);
	init_pair(2, P_RUBY, COLOR_BLACK);
	init_pair(3, P_EMERALD, COLOR_BLACK);
	init_pair(4, P_SAPHIR, COLOR_BLACK);
	init_pair(5, P_MAGEN, COLOR_BLACK);
	init_pair(22, I_BLUE, P_RUBY);
	init_pair(23, I_BLUE, P_EMERALD);
	init_pair(24, I_BLUE, P_SAPHIR);
	init_pair(25, I_BLUE, P_MAGEN);
	init_pair(6, I_BLUE, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, I_BLUE);
	init_pair(9, COLOR_BLACK, 161);
	init_pair(8, 161, COLOR_BLACK);
	init_pair(9, COLOR_BLACK, 231);
	init_pair(10, 231, 161);
	init_pair(11, COLOR_BLACK, 161);
	init_pair(12, COLOR_BLACK, 136);
	init_pair(13, COLOR_BLACK, P_GOLD);
	init_pair(32, PP_RUBY, COLOR_BLACK);
	init_pair(33, PP_EMERALD, COLOR_BLACK);
	init_pair(34, PP_SAPHIR, COLOR_BLACK);
	init_pair(35, PP_MAGEN, COLOR_BLACK);
}

void	ft_init_ncurses(t_vm *vm)
{
	setlocale(LC_ALL, "");
	initscr();
	timeout(0);
	noecho();
	start_color();
	curs_set(0);
	ft_init_color();
	getmaxyx(stdscr, vm->screen.y, vm->screen.x);
	vm->ui.line_len = vm->screen.x * 90 / 100;
	vm->ui.line_marge = (vm->screen.x - (vm->screen.x * 90 / 100)) / 2;
	vm->ui.speed = 500;
	vm->ui.pause = 1;
	vm->ui.tpt = 0;
	ft_init_map_bu(vm);
	ft_display_ui(vm);
	ft_init_display(vm, -1, -1);
}
