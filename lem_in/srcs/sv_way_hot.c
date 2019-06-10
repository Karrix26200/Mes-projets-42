/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sv_way_hot.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tvarnier <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/13 15:50:28 by tvarnier     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 15:53:01 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	way_hot(t_ant *node, int path, int len)
{
	int		i;

	node->hot = len;
	i = -1;
	while (node->chd && node->chd[++i])
		if (node->chd[i]->path == path && node->chd[i]->hot == -2)
			way_hot(node->chd[i], path, len + 1);
}

void	new_hot(t_data *data, t_res res)
{
	int		path;
	int		i;

	reset_hot(data->ant_hill);
	path = -1;
	while (++path < res.nbr_ways)
	{
		i = -1;
		while (data->end->chd && data->end->chd[++i])
			if (data->end->chd[i]->path == path)
				way_hot(data->end->chd[i], path, 1);
	}
}
