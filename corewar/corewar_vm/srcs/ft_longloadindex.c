/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_longloadindex.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 08:50:14 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 09:19:47 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_lldi(t_process *process, t_mem *mem, int verb, t_player **players)
{
	ft_ldi(process, mem, verb, players);
	if (process && mem && verb && players)
		;
}
