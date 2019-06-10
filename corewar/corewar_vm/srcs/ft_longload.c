/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_longload.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 08:49:49 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 14:51:39 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_dir_lld(t_mem *mem, t_process *process,
	int *reg, long *data_to_store)
{
	int		i;

	i = 4;
	mem = mem->next->next;
	while (i-- > 0)
	{
		*data_to_store += (mem->byte << (i * 8));
		mem = mem->next;
	}
	if (mem->byte > 0 && mem->byte < 17)
	{
		*reg = (int)mem->byte - 1;
		process->reg[*reg] = *data_to_store;
		process->carry = *data_to_store == 0 ? 1 : 0;
	}
	process->pc = 7;
}

void	ft_lld(t_process *process, t_mem *mem, int verb, t_player **players)
{
	long	data_to_store;
	int		reg;

	data_to_store = 0;
	if (players && ((unsigned char)mem->next->byte & 0xf0)
		== (DIR_CODE << 6) + (REG_CODE << 4))
		ft_dir_lld(mem, process, &reg, &data_to_store);
	else if (((unsigned char)mem->next->byte & 0xf0)
		== (IND_CODE << 6) + (REG_CODE << 4))
	{
		if (mem->next->next->next->next->byte - 1 >= 0
			&& mem->next->next->next->next->byte - 1 < 16)
			reg = mem->next->next->next->next->byte - 1;
		else
			return ;
		data_to_store = (get_ind_val(mem, mem->next->next, 0) >> 16);
		process->reg[reg] = data_to_store;
		process->carry = process->reg[reg] == 0 ? 1 : 0;
		process->pc = 5;
	}
	if ((verb & 4))
		ft_printf("P %4d | lld %d r%d\n", process->nb, data_to_store, reg + 1);
}
