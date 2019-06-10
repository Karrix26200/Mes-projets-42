/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_instruction.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 19:59:23 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 07:21:32 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_op	**ft_init_instruction_list(void)
{
	t_op	**instructions;

	if (!(instructions = (t_op **)malloc(17 * sizeof(t_op *))))
		return (NULL);
	instructions[0] = ft_new_op(0x01, &ft_live, 10);
	instructions[1] = ft_new_op(0x02, &ft_ld, 5);
	instructions[2] = ft_new_op(0x03, &ft_st, 5);
	instructions[3] = ft_new_op(0x04, &ft_add, 10);
	instructions[4] = ft_new_op(0x05, &ft_sub, 10);
	instructions[5] = ft_new_op(0x06, &ft_and, 6);
	instructions[6] = ft_new_op(0x07, &ft_or, 6);
	instructions[7] = ft_new_op(0x08, &ft_xor, 6);
	instructions[8] = ft_new_op(0x09, &ft_zjmp, 20);
	instructions[9] = ft_new_op(0x0a, &ft_ldi, 25);
	instructions[10] = ft_new_op(0x0b, &ft_sti, 25);
	instructions[11] = ft_new_op(0x0c, &ft_fork, 800);
	instructions[12] = ft_new_op(0x0d, &ft_lld, 10);
	instructions[13] = ft_new_op(0x0e, &ft_lldi, 50);
	instructions[14] = ft_new_op(0x0f, &ft_lfork, 1000);
	instructions[15] = ft_new_op(0x10, &ft_aff, 2);
	instructions[16] = 0;
	return (instructions);
}

t_mem	*dup_mem(t_mem *to_dup, t_mem *prev)
{
	t_mem	*mem;

	if (to_dup == NULL)
		return (NULL);
	if (!(mem = (t_mem *)malloc(sizeof(t_mem))))
		return (NULL);
	mem->byte = to_dup->byte;
	mem->addr = to_dup->addr;
	mem->player = to_dup->player;
	mem->next = NULL;
	mem->prev = prev;
	return (mem);
}

t_mem	*get_instructions(int pc, t_mem *mem)
{
	t_mem	*instr;
	t_mem	*curr;
	t_mem	*prev;

	curr = NULL;
	instr = NULL;
	while (pc--)
	{
		if (instr == NULL)
		{
			instr = dup_mem(mem, NULL);
			prev = instr;
			curr = instr;
		}
		else
		{
			curr->next = dup_mem(mem, prev);
			prev = curr;
			curr = curr->next;
		}
		mem = mem->next;
	}
	return (instr);
}

void	ft_exec_instructions(t_process *process, t_op **instructions,
		t_vm *vm, int verbosity)
{
	int		check_v16;

	check_v16 = 0;
	if (process->opcode > 0 && process->opcode < 17)
	{
		if (ft_check_ocp(process->mem, process->opcode))
			instructions[(int)process->opcode - 1]->ft(process,
				process->mem, verbosity, vm->players);
		else
			process->pc = ft_get_pc(process, vm->instructions, 2);
		while (vm->process->prev)
			vm->process = vm->process->prev;
		process->cast = -1;
	}
	if ((verbosity & 16) && process->pc > 1 && (check_v16 = 1))
		ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", process->pc,
			process->mem->addr, process->mem->addr + process->pc);
	while (process && process->pc--)
	{
		if (check_v16 == 1)
			ft_printf("%.2x ", process->mem->byte);
		process->mem = process->mem->next;
	}
	if (process && !(process->pc = 0) && check_v16 == 1)
		ft_printf("\n");
}
