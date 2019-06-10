/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sv_send_move.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tvarnier <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/13 16:02:14 by tvarnier     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 16:08:57 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		link_start_end(t_data *data)
{
	int		i;

	i = -1;
	while (data->end->chd && data->end->chd[++i])
		if (data->end->chd[i]->hot == START)
			return (1);
	return (0);
}

int		move_ant(t_ant *dest, t_ant *from, int tour)
{
	dest->ant = from->ant;
	if (from->hot > 0)
		from->ant = NO_ANT;
	else if (from->hot == START)
		from->ant = (from->ant - 1 > 0) ? from->ant - 1 : 0;
	dest->tour = tour;
	ft_putchar('L');
	ft_putnbr(dest->ant);
	ft_putchar('-');
	ft_putstr(dest->name);
	ft_putchar(' ');
	return (1);
}
