/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_loadindex.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 08:43:43 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 18:40:45 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		ft_get_idx2_arg(t_mem **mem, int l2, t_process *process, int *p)
{
	if (l2 == -1)
	{
		if ((*mem)->byte - 1 < 0 || (*mem)->byte - 1 > 15)
			return (0);
		*p = process->reg[(int)(*mem)->byte - 1];
		(*mem) = (*mem)->next;
	}
	else if (l2 == 0)
		return (0);
	else if (l2 != -2)
	{
		while (l2--)
		{
			if ((*mem)->byte & 128)
				*p += ((256 + (char)(*mem)->byte) << (8 * l2));
			else
				*p += ((*mem)->byte << (8 * l2));
			*mem = (*mem)->next;
		}
		*p = (short)(*p);
	}
	else
		return (0);
	return (1);
}

int		get_idxarg_size(int *l1, int *addr, t_mem **mem, t_process *process)
{
	int		l2;

	*addr = 0;
	*l1 = ((*mem)->next->byte >> 6) ? 2 : 0;
	l2 = (((*mem)->next->byte >> 4) & 0x03) ? 2 : 0;
	if ((((*mem)->next->byte >> 6) != DIR_CODE))
		*l1 -= ((*mem)->next->byte >> 6) == REG_CODE ? 3 : 2;
	if ((((*mem)->next->byte >> 4) & 0x03) != DIR_CODE)
		l2 -= (((*mem)->next->byte >> 4) & 0x03) == REG_CODE ? 3 : 2;
	process->pc = get_opsize(((*mem)->next->byte >> 6), 2)
		+ get_opsize((((*mem)->next->byte >> 4) & 0x03), 2)
			+ get_opsize((((*mem)->next->byte >> 2) & 0x03), 2) + 2;
	if ((((*mem)->next->byte >> 2) & 0x03) != REG_CODE)
		return (-9);
	*addr = (*mem)->addr;
	(*mem) = (*mem)->next->next;
	return (l2);
}

void	ldi_goto(t_process *process, t_mem **mem,
			t_ldi *param, t_player **players)
{
	int		i;

	i = 0;
	*mem = process->mem;
	param->p1 = process->opcode == 0x0a
		? param->p1 % IDX_MOD : param->p1;
	while (players && i != param->p1)
	{
		*mem = param->p1 < 0 ? (*mem)->prev : (*mem)->next;
		i += param->p1 < 0 ? -1 : 1;
	}
}

void	ldi_end(t_process *process, t_mem *mem, t_ldi param, int verb)
{
	int		i;

	if (!(i = 0) && param.reg >= 0 && param.reg <= 15)
	{
		process->reg[param.reg] = 0;
		param.addr = mem->addr > param.addr && param.p1 < 0
			? mem->addr - 4096 : mem->addr;
		param.addr = process->opcode == 0x0e
			? (param.param1 + param.p2 + process->mem->addr) : param.addr;
		while (i++ < REG_SIZE)
		{
			process->reg[param.reg] += (mem->byte << ((REG_SIZE - i) * 8));
			mem = mem->next;
		}
		if (process->opcode == 0x0e)
			process->carry = process->reg[param.reg] == 0 ? 1 : 0;
		if ((verb & 4))
			ft_printf("P %4d | %s %d %d r%d%s%d + %d = %d (with %s %d)\n",
				process->nb, process->opcode == 0x0e ? "lldi" : "ldi",
						param.param1, param.p2, param.reg + 1,
							"\n       | -> load from ", param.param1,
								param.p2, param.param1 + param.p2,
									process->opcode == 0x0e ? "pc"
										: "pc and mod", param.addr);
	}
}

void	ft_ldi(t_process *process, t_mem *mem, int verb, t_player **players)
{
	t_ldi	param;
	int		i;

	param.p1 = 0;
	param.p2 = 0;
	if ((param.l2 = get_idxarg_size(&param.l1,
		&param.addr, &mem, process)) == -9 || !ft_get_idx_arg(&mem,
			param.l1, process, &param.p1) || !ft_get_idx2_arg(&mem,
				param.l2, process, &param.p2))
		return ;
	param.param1 = param.p1;
	param.p1 += param.p2;
	param.reg = mem->byte - 1;
	ldi_goto(process, &mem, &param, players);
	i = 0;
	ldi_end(process, mem, param, verb);
}
