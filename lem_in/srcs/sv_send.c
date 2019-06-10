/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sv_send.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tvarnier <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 14:29:19 by tvarnier     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 16:02:59 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		should_push(long ant, t_res res, int path)
{
	int		i;
	int		without;
	int		with;

	path += (res.direct) ? 1 : 0;
	i = -1;
	without = 0;
	while (++i < path)
		without += res.way[i][1];
	if (without == 0)
		return (1);
	with = without + res.way[path][1];
	if ((((float)without / (float)path) + ((float)ant / (float)path)) >
		((float)with / (float)(path + 1)) + ((float)ant / (float)(path + 1)))
		return (1);
	return (0);
}

int		push_start(t_data *data, t_ant *start, t_res res, int tour)
{
	int		i;
	int		path;
	int		n_path;

	if (start->ant > 0)
	{
		if (res.direct)
			move_ant(data->end, start, tour);
		path = -1;
		while (++path < res.nbr_ways)
		{
			i = -1;
			n_path = res.way[path + res.direct][0];
			while (start->chd && start->chd[++i])
				if (start->chd[i]->path == n_path
						&& should_push(start->ant, res, path))
				{
					move_ant(start->chd[i], start, tour);
					break ;
				}
		}
		return (1);
	}
	return (0);
}

int		drag_way(t_ant *node, t_ant *from, int tour)
{
	int		tmp;
	int		i;

	tmp = 0;
	if (node->ant != NO_ANT && (tmp = 1))
		move_ant(from, node, tour);
	i = -1;
	while (node->chd && node->chd[++i])
		if (node->chd[i]->path == node->path && node->chd[i]->hot > node->hot)
		{
			tmp = (drag_way(node->chd[i], node, tour) ? 1 : tmp);
			break ;
		}
	return (tmp);
}

int		drag_ant(t_ant *end, int tour)
{
	int		i;
	int		tmp;

	tmp = 0;
	i = -1;
	while (end->chd && end->chd[++i])
	{
		if (end->chd[i]->path >= 0)
			tmp = (drag_way(end->chd[i], end, tour)) ? 1 : tmp;
	}
	return (tmp);
}

int		sv_send(t_data *data, t_res res)
{
	int		tour;
	int		oneant;

	res.direct = link_start_end(data);
	res.total_length += res.direct + res.nbr_ways;
	res.way = get_way(data, res);
	data->start->ant = data->nb_ant;
	tour = 0;
	oneant = 1;
	while (oneant)
	{
		oneant = drag_ant(data->end, tour);
		oneant = (push_start(data, data->start, res, tour)) ? 1 : oneant;
		if (oneant)
			ft_putchar('\n');
		tour++;
	}
	free_tab(&(res.way), res.nbr_ways + res.direct);
	return (1);
}
