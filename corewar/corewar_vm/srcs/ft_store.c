/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_store.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 08:31:23 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 14:55:26 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		ft_ind_st(t_mem *mem, int *reg, short *addr, t_process *process)
{
	t_mem	*pmem;
	int		i;
	long	data_from_reg;

	pmem = process->mem;
	if (!(i = 0) && mem->next->next->byte > 0 && mem->next->next->byte < 17)
		data_from_reg =
			process->reg[(*reg = (int)mem->next->next->byte) - 1];
	else
		return (0);
	*addr = ((mem->next->next->next->byte << 8)
		| mem->next->next->next->next->byte);
	while (i != *addr % IDX_MOD)
	{
		pmem = *addr % IDX_MOD < 0 ? pmem->prev : pmem->next;
		i += *addr % IDX_MOD < 0 ? -1 : 1;
	}
	i = 0;
	while (i++ < REG_SIZE)
	{
		pmem->byte = (char)(data_from_reg >> ((REG_SIZE - i) * 8));
		pmem->player = process->player;
		pmem = pmem->next;
	}
	return (process->pc = 5);
}

void	ft_st(t_process *process, t_mem *mem, int verb, t_player **players)
{
	short	addr;
	int		reg;

	if (players && ((unsigned char)mem->next->byte & 0xf0)
		== (REG_CODE << 6) + (IND_CODE << 4)
			&& !ft_ind_st(mem, &reg, &addr, process))
		return ;
	else if (((unsigned char)mem->next->byte & 0xf0)
		== (REG_CODE << 6) + (REG_CODE << 4)
			&& mem->next->next->next->byte > 0
				&& mem->next->next->next->byte < 17
					&& mem->next->next->byte > 0
						&& mem->next->next->byte < 17)
	{
		addr = (int)mem->next->next->next->byte;
		reg = (int)mem->next->next->byte;
		process->reg[addr - 1] = process->reg[reg - 1];
		process->pc = 4;
	}
	if ((verb & 4))
		ft_printf("P %4d | st r%d %d\n", process->nb, reg, addr);
}
