/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_operations.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sbedene <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/13 12:30:01 by sbedene      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 16:51:51 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		get_nb_player(t_player **players)
{
	int		i;

	i = 0;
	while (players[i])
		i++;
	return (i);
}

int		get_ind_val(t_mem *start, t_mem *mem, int mod)
{
	int		val;
	int		i;
	short	addr;

	addr = ((mem->byte << 8) | mem->next->byte);
	addr = mod == 1 ? addr % IDX_MOD : addr;
	i = 0;
	while (i != addr)
	{
		start = addr < 0 ? start->prev : start->next;
		i += addr < 0 ? -1 : 1;
	}
	i = 0;
	val = 0;
	while (i++ < 4)
	{
		val += (start->byte << ((4 - i) * 8));
		start = start->next;
	}
	return (val);
}

int		ft_get_op_arg(t_mem **mem, int l1, t_process *process, int *p)
{
	*p = 0;
	if (l1 == 1)
	{
		if ((*mem)->byte < 1 || (*mem)->byte > 16)
			return (0);
		*p = process->reg[(int)(*mem)->byte - 1];
		*mem = (*mem)->next;
	}
	else if (l1 == 2)
	{
		*p = get_ind_val(process->mem, (*mem), 1);
		*mem = (*mem)->next->next;
	}
	else
		while (l1--)
		{
			*p = ((*p) | ((*mem)->byte << (8 * l1)));
			*mem = (*mem)->next;
		}
	return (1);
}

int		ft_get_idx_arg(t_mem **mem, int l1, t_process *process, int *p)
{
	*p = 0;
	if (l1 == -1)
	{
		if ((*mem)->byte < 1 || (*mem)->byte > 16)
			return (0);
		*p = process->reg[(int)(*mem)->byte - 1];
		*mem = (*mem)->next;
	}
	else if (l1 == 0)
	{
		*p = get_ind_val(process->mem, (*mem), 1);
		*mem = (*mem)->next->next;
	}
	else if (l1 != -2)
	{
		while (l1--)
		{
			*p = ((*p) | ((*mem)->byte << (8 * l1)));
			*mem = (*mem)->next;
		}
		*p = (short)*p;
	}
	else
		return (0);
	return (1);
}
