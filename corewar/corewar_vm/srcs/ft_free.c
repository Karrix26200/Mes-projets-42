/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 17:29:35 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 12:38:19 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_free_mem(t_vm *vm)
{
	while (vm->mem && vm->mem->next)
	{
		if (vm->mem && vm->mem->prev)
			vm->mem->prev->next = NULL;
		vm->mem = vm->mem->next;
		free(vm->mem->prev);
		vm->mem->prev = NULL;
	}
	free(vm->mem);
}

void	ft_free_players(t_vm *vm)
{
	int		i;

	i = -1;
	while (vm->players && vm->players[++i])
	{
		ft_strdel(&vm->players[i]->buffer);
		ft_strdel(&vm->players[i]->name);
		ft_strdel(&vm->players[i]->comment);
		free(vm->players[i]);
	}
	free(vm->players);
}

void	ft_free_instructions(t_vm *vm)
{
	int		i;

	i = -1;
	while (vm->instructions && vm->instructions[++i])
		free(vm->instructions[i]);
	if (vm->instructions)
		free(vm->instructions);
}

void	ft_free_process(t_vm *vm)
{
	t_process	*tmp;

	while (vm->process)
	{
		free(vm->process->reg);
		tmp = vm->process->next;
		free(vm->process);
		vm->process = tmp;
	}
	while (vm->dead_process)
	{
		free(vm->dead_process->reg);
		tmp = vm->dead_process->next;
		free(vm->dead_process);
		vm->dead_process = tmp;
	}
}

int		ft_free(t_vm *vm, t_args *args)
{
	int i;

	i = 0;
	if (args)
		free(args);
	ft_free_mem(vm);
	ft_free_players(vm);
	ft_free_process(vm);
	while (i < 16)
		free(vm->instructions[i++]);
	free(vm->instructions);
	free(vm);
	return (-1);
}
