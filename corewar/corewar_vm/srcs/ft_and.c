/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_and.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 08:41:36 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 10:12:25 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_and(t_process *process, t_mem *mem, int verb, t_player **players)
{
	int		l1;
	int		l2;
	int		p1;
	int		p2;

	l1 = 4;
	l2 = 4;
	if (players && ((mem->next->byte >> 6) != DIR_CODE))
		l1 -= (mem->next->byte >> 6) == REG_CODE ? 3 : 2;
	if (((mem->next->byte >> 4) & 0x03) != DIR_CODE)
		l2 -= ((mem->next->byte >> 4) & 0x03) == REG_CODE ? 3 : 2;
	mem = mem->next->next;
	process->pc = l1 + l2 + 3;
	if (!ft_get_op_arg(&mem, l1, process, &p1)
		|| !ft_get_op_arg(&mem, l2, process, &p2))
		return ;
	if (mem->byte > 0 && mem->byte < 17)
	{
		process->reg[(int)mem->byte - 1] = (int)(p1 & p2);
		if ((verb & 4))
			ft_printf("P %4d | and %d %d r%d\n",
				process->nb, p1, p2, (int)mem->byte);
		process->carry = process->reg[(int)mem->byte - 1] == 0 ? 1 : 0;
	}
}
