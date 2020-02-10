/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/10 22:14:24 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 14:58:28 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		ft_get_pc(t_process *process, t_op **instructions, int caze)
{
	int		dir;

	dir = process->opcode < 0x09 || process->opcode == 0x0d ? 4 : 2;
	if (((process->mem->byte <= 0 || process->mem->byte > 16) && caze == 1))
		return (1);
	process->cast = process->opcode > 0 && process->opcode < 17
		? instructions[(int)process->opcode - 1]->cast : -1;
	if (process->opcode == 0x01)
		return (5);
	else if (process->opcode == 0x09
			|| process->opcode == 0x0c || process->opcode == 0x0f)
		return (3);
	else if (process->opcode == 0x02
			|| process->opcode == 0x03 || process->opcode == 0x0d)
		return (get_opsize((process->mem->next->byte >> 6), dir)
			+ get_opsize(((process->mem->next->byte >> 4) & 0x03), dir) + 2);
	else if (process->opcode == 0x10)
		return (get_opsize(process->mem->next->byte >> 6, 8) + 2);
	else
	{
		return (get_opsize((process->mem->next->byte >> 6), dir)
				+ get_opsize(((process->mem->next->byte >> 4) & 0x03), dir) + 2
				+ get_opsize(((process->mem->next->byte >> 2) & 0x03), dir));
	}
	return (0xcaca);
}

void	ft_process_operations(t_process *process,
		t_op **instructions, t_vm *vm, int verbosity)
{
	int		check_v16;
	int		i;

	i = 0;
	while (process)
	{
		check_v16 = 0;
		if (process->lcycle == -1)
			process->lcycle += vm->cycle;
		if (process->pc == 0)
		{
			process->opcode = process->mem->byte;
			process->pc = ft_get_pc(process, vm->instructions, 1);
		}
		if (process->cast > 0)
			process->cast--;
		if (process->cast == 0 || process->opcode <= 0 || process->opcode > 16)
			ft_exec_instructions(process, instructions, vm, verbosity);
		i++;
		process = process->next;
	}
}

void	init_loop(t_loop *loop, t_vm *vm, t_args *args)
{
	loop->check = 0;
	loop->death = vm->death;
	loop->last_live = -vm->nb_players;
	loop->wait = NULL;
	loop->live = 0;
	args->verbosity = args->verbosity == -1 ? 0 : args->verbosity;
}

int		main(int ac, char *av[])
{
	t_args	*args;
	t_vm	*vm;
	int		i;

	vm = NULL;
	if (!(vm = ft_init_vm(vm)))
		return (-1);
	args = NULL;
	vm->instructions = ft_init_instruction_list();
	if (!(args = ft_get_args(ac, av, args, vm))
			|| !(vm->mem = ft_init_vm_mem(vm)))
		return (ft_free(vm, args));
	vm->process = ft_init_process(vm);
	ft_printf("Introducing contestants...\n");
	i = -1;
	vm->players[0]->aff = args->aff ? 1 : 0;
	while (vm->players[++i])
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
				vm->players[i]->prog_size, vm->players[i]->name,
				vm->players[i]->comment);
	if (args->ncurse)
		ft_init_ncurses(vm);
	ft_loop(args, vm);
	ft_free(vm, args);
	return (0);
}
