/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_operations4.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sbedene <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/13 12:32:58 by sbedene      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 13:29:44 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_aff(t_process *process, t_mem *mem, int verb, t_player **players)
{
	if (players && ((mem->next->byte >> 6) & 0x03) == REG_CODE)
	{
		process->pc = 3;
		if (mem->next->next->byte >= 1 && mem->next->next->byte <= 16)
		{
			if ((verb & 4))
				ft_printf("Aff: %c\n",
					process->reg[(mem->next->next->byte - 1)] % 256);
			if (process->reg[(mem->next->next->byte) - 1] % 256 == 0)
				process->carry = 1;
			else
				process->carry = 0;
		}
	}
	else if (((mem->next->byte >> 6) & 0x03) == DIR_CODE)
		process->pc = 6;
	else if (((mem->next->byte >> 6) & 0x03) == IND_CODE)
		process->pc = 4;
}
