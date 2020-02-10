/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_loop.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 20:07:07 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 08:06:45 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static long	init_values(t_loop *loop, t_vm *vm, t_args *args, int *i)
{
	init_loop(loop, vm, args);
	*i = 1;
	return (get_microtime());
}

static void	make_a_turn(t_vm *vm, t_args *args, t_loop *loop, int *i)
{
	vm->cycle++;
	if (args->verbosity & 2)
		ft_printf("It is now cycle %d\n", vm->cycle);
	if (vm->process)
		ft_process_operations(vm->process, vm->instructions,
			vm, args->verbosity);
	vm->process = vm->process->prev ? vm->process->prev : vm->process;
	if (vm->death < 0 || vm->cycle == loop->death)
		loop->death += check_death(vm, &loop->check, &loop->last_live, args);
	(*i)++;
}

void		ft_loop(t_args *args, t_vm *vm)
{
	t_loop	loop;
	int		i;
	long	timestamp;

	timestamp = init_values(&loop, vm, args, &i);
	while (vm->process)
	{
		if (args->ncurse == 0
			|| (get_microtime() > timestamp + 1000000 / vm->ui.speed * i
				&& (vm->ui.pause == 0 || vm->ui.tpt == 1)))
			make_a_turn(vm, args, &loop, &i);
		if (args->ncurse)
			ft_display_update(vm, &i, &timestamp);
		else if (vm->cycle == args->dump && ft_print_mem(vm))
			break ;
		else if (args->pause != -1 && vm->cycle % args->pause == 0
			&& ft_print_mem(vm))
			get_next_line(0, &loop.wait);
	}
	if (!vm->process && args->ncurse == 1)
		ft_display_end(vm, -loop.last_live - 1);
	else if (!vm->process)
		ft_printf("Contestant %d, \"%s\", has won !\n",
			-loop.last_live, vm->players[-loop.last_live - 1]->name);
}
