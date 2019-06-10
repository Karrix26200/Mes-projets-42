/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sub.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 08:32:40 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 14:57:00 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_sub(t_process *process, t_mem *mem, int verb, t_player **players)
{
	int		reg_a;
	int		reg_b;
	int		reg_c;

	if (players && (mem->next->byte & 0xfc)
		== (REG_CODE << 6) + (REG_CODE << 4) + (REG_CODE << 2))
	{
		reg_c = (int)mem->next->next->next->next->byte;
		reg_a = (int)mem->next->next->byte;
		reg_b = (int)mem->next->next->next->byte;
		process->reg[reg_c - 1] = process->reg[reg_a - 1]
			- process->reg[reg_b - 1];
		process->carry = process->reg[reg_c - 1] == 0 ? 1 : 0;
		if ((verb & 4))
			ft_printf("P %4d | sub r%d r%d r%d\n",
				process->nb, reg_a, reg_b, reg_c);
		process->pc = 5;
	}
}
