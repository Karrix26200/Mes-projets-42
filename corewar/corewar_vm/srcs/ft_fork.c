/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fork.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 08:49:01 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 08:57:30 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_process	*ft_dup_proc(t_process *to_dup, t_process *first, int init_player)
{
	t_process	*process;
	static int	number = 0;
	int			i;

	number = number == 0 ? init_player : number;
	if (!(process = (t_process *)malloc(sizeof(t_process)))
	|| !(process->reg = (long *)malloc(sizeof(long) * 16)))
		return (NULL);
	process->next = first;
	i = -1;
	while (++i < 16)
		process->reg[i] = to_dup->reg[i];
	process->carry = to_dup->carry;
	process->pc = 0;
	process->last_live = 0;
	process->lcycle = to_dup->lcycle;
	process->mem = to_dup->mem;
	process->opcode = to_dup->opcode;
	process->cast = -1;
	process->prev = NULL;
	process->player = to_dup->player;
	process->live = to_dup->live;
	process->nb = number++;
	process->mem_bu = NULL;
	return (process);
}

void		ft_fork(t_process *process,
	t_mem *mem, int verb, t_player **players)
{
	t_process	*first;
	int			i;
	short		diff;

	first = process;
	while (first->prev)
		first = first->prev;
	first->prev = ft_dup_proc(process, first, get_nb_player(players) + 1);
	first->prev->prev = NULL;
	i = -1;
	while (++i < 16)
		first->prev->reg[i] = process->reg[i];
	ft_zjmp(first->prev, process->mem, 0, players);
	diff = ((mem->next->byte << 8) | mem->next->next->byte);
	if ((verb & 4))
		ft_printf("P %4d | %s %d (%d)\n", process->nb,
			process->opcode == 0x0f ? "lfork" : "fork",
				diff, process->opcode == 0x0f
					? process->mem->addr + diff
						: process->mem->addr + (diff % IDX_MOD));
	first->prev->opcode = first->prev->mem->byte;
	if (process && mem && verb && players)
		;
}
