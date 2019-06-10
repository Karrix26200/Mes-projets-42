/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_longfork.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 08:50:46 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 09:19:28 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_lfork(t_process *process, t_mem *mem, int verb, t_player **players)
{
	if (process && mem && verb && players)
		;
	ft_fork(process, mem, verb, players);
}
