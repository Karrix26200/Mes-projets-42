/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_load.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 08:30:49 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 14:49:27 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		ft_direct_ld(t_process *process, t_mem **mem, int *reg,
		long *data_to_store)
{
	int		i;

	i = 4;
	*mem = (*mem)->next->next;
	*data_to_store = 0;
	while (i-- > 0)
	{
		*data_to_store |= ((*mem)->byte << (i * 8));
		(*mem) = (*mem)->next;
	}
	if ((*mem)->byte > 0 && (*mem)->byte < 17)
	{
		*reg = (int)(*mem)->byte - 1;
		process->reg[*reg] = *data_to_store;
		process->carry = *data_to_store == 0 ? 1 : 0;
	}
	else
		return (0);
	process->pc = 7;
	return (1);
}

void	ft_ld(t_process *process, t_mem *mem, int verb, t_player **players)
{
	long	data_to_store;
	int		i;
	int		reg;

	data_to_store = 0;
	if (players && ((unsigned char)mem->next->byte & 0xf0)
		== (DIR_CODE << 6) + (REG_CODE << 4)
			&& !ft_direct_ld(process, &mem, &reg, &data_to_store))
		return ;
	if (((unsigned char)mem->next->byte & 0xf0)
		== (IND_CODE << 6) + (REG_CODE << 4))
	{
		i = 0;
		reg = mem->next->next->next->next->byte - 1;
		data_to_store = get_ind_val(mem, mem->next->next, 1);
		process->reg[reg] = data_to_store;
		if (process->reg[reg] == 0)
			process->carry = 1;
		else
			process->carry = 0;
		process->pc = 5;
	}
	if ((verb & 4))
		ft_printf("P %4d | ld %d r%d\n", process->nb, data_to_store, reg + 1);
}
