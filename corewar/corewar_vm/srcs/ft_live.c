/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_live.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 08:29:57 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 09:15:49 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	ft_live(t_process *process, t_mem *mem, int verb, t_player **players)
{
	int		player;
	int		i;
	int		nb_player;

	process->live++;
	players[0]->nb_live++;
	nb_player = get_nb_player(players);
	player = 0;
	i = 4;
	mem = mem->next;
	while (i--)
	{
		player = (player | (mem->byte) << (8 * i));
		mem = mem->next;
	}
	if ((verb & 4))
		ft_printf("P %4d | live %d\n", process->nb, player);
	if (player < 0 && player >= -nb_player)
	{
		if ((verb & 1))
			ft_printf("Player %d (%s) is said to be alive\n",
					-player, players[-player - 1]->name);
		process->last_live = player;
	}
	process->lcycle = -1;
}
