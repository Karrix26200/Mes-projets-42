/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ncurses_utils.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 02:43:54 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/18 02:43:56 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

long	get_microtime(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * (int)1e6 + current_time.tv_usec);
}

int		rand_a_b(int a, int b)
{
	return (rand() % (b - a) + a);
}

int		ft_get_center(int base_len, int target_len)
{
	return (((base_len - target_len) > 0 ? (base_len - target_len) :
				-(base_len - target_len)) / 2);
}

void	ft_init_display(t_vm *vm, int y, int x)
{
	while (++y < 64)
	{
		x = -1;
		while (++x < 64)
		{
			if (vm->mem->player != -1)
			{
				attron(COLOR_PAIR(vm->mem->player + 2));
				mvprintw(y, (x * 4) + ((vm->screen.x - (64 * 4)) / 2),
				" %.2X ", vm->mem->byte);
			}
			vm->mem = vm->mem->next;
		}
		refresh();
		usleep(20000);
	}
}
