/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_zjmp.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 08:43:06 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 19:19:49 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_zjmp(t_process *process, t_mem *mem, int verb, t_player **players)
{
	short			len;
	int				i;
	short			real_len;
	unsigned char	opcode;

	i = 2;
	opcode = process->mem->byte;
	len = (((mem->next->byte) << 8) | (mem->next->next->byte));
	mem = mem->next->next->next;
	real_len = process->opcode == 0x0c || process->opcode == 0x09 ?
		len % IDX_MOD : len;
	if (players && !(process->carry == 0 && process->opcode
		!= 0x0c && process->opcode != 0x0f) && !(i = 0))
	{
		while (i != real_len)
		{
			process->mem = real_len < 0
				? process->mem->prev : process->mem->next;
			i += real_len < 0 ? -1 : 1;
		}
		process->pc = 0;
	}
	if ((verb & 4))
		ft_printf("P %4d | zjmp %d %s\n",
			process->nb, len, process->carry ? "OK" : "FAILED");
}
