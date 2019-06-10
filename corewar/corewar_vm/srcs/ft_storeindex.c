/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_storeindex.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 08:48:18 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 19:07:28 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		get_stiarg_size(t_ldi *param, int *new_pc, t_mem *mem)
{
	param->l1 = 2;
	param->l2 = 2;
	param->p1 = 0;
	param->p2 = 0;
	if (((mem->next->byte >> 4) & 0x03) != DIR_CODE)
		param->l1 -= ((mem->next->byte >> 4) & 0x03) == REG_CODE ? 3 : 2;
	if (((mem->next->byte >> 2) & 0x03) != DIR_CODE)
		param->l2 -= ((mem->next->byte >> 2) & 0x03) == REG_CODE ? 3 : 2;
	param->reg = mem->next->next->byte - 1;
	if (param->reg < 0 || param->reg > 15)
		return (0);
	*new_pc = 5;
	if (((mem->next->byte >> 4) & 0x03) != REG_CODE)
		(*new_pc)++;
	if (((mem->next->byte >> 2) & 0x03) != REG_CODE)
		(*new_pc)++;
	return (1);
}

int		ft_stifirst(t_ldi *param, t_mem **mem, t_process *process)
{
	(*mem) = (*mem)->next->next->next;
	if (param->l1 == -1)
	{
		if ((*mem)->byte < 1 || (*mem)->byte > 16)
			return (0);
		param->p1 = process->reg[(int)(*mem)->byte - 1];
		*mem = (*mem)->next;
	}
	else if (param->l1 == 0)
	{
		param->p1 = get_ind_val(process->mem, *mem, 0);
		*mem = (*mem)->next->next;
	}
	else
	{
		param->p1 = (short)(((*mem)->byte << 8) | (*mem)->next->byte);
		*mem = (*mem)->next->next;
	}
	return (1);
}

int		ft_stisec(t_ldi *param, t_mem **mem, t_process *process)
{
	if (param->l2 == -1)
	{
		if ((*mem)->byte < 1 || (*mem)->byte > 16)
			return (0);
		param->p2 = process->reg[(int)(*mem)->byte - 1];
		(*mem) = (*mem)->next;
	}
	else if (param->l2 == 0)
		return (0);
	else
	{
		param->p2 = (short)(((*mem)->byte << 8) | (*mem)->next->byte);
		(*mem) = (*mem)->next->next;
	}
	return (1);
}

void	sti_goto(t_process *process, t_ldi *param, t_mem **mem)
{
	int		i;

	i = 0;
	*mem = process->mem;
	while (i != param->p1)
	{
		*mem = param->p1 < 0 ? (*mem)->prev : (*mem)->next;
		i += param->p1 < 0 ? -1 : 1;
	}
	param->addr = process->mem->addr + i;
	i = 0;
	while (i++ < REG_SIZE)
	{
		(*mem)->byte = (process->reg[param->reg] >> ((REG_SIZE - i) * 8));
		(*mem)->player = process->player;
		(*mem) = (*mem)->next;
	}
}

void	ft_sti(t_process *process, t_mem *mem, int verb, t_player **players)
{
	t_ldi	param;
	int		new_pc;

	if ((players && !get_stiarg_size(&param, &new_pc, mem))
		|| !ft_stifirst(&param, &mem, process)
			|| !ft_stisec(&param, &mem, process))
		return ;
	param.param1 = param.p1;
	param.p1 += param.p2;
	param.p1 = param.p1 % IDX_MOD;
	sti_goto(process, &param, &mem);
	process->pc = new_pc;
	if ((verb & 4))
		ft_printf("P %4d | sti r%d %d %d%s%d + %d = %d (with pc and mod %d)\n",
			process->nb, param.reg + 1, param.param1, param.p2,
			"\n       | -> store to ", param.param1, param.p2,
				param.param1 + param.p2, param.addr);
}
