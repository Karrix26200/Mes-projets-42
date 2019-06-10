/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tvarnier <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/07 03:42:39 by tvarnier     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 15:54:30 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		save_res(t_data *data, t_res *res, int len, int path)
{
	if (res->nbr_ways == 0
			|| (((float)res->total_length / (float)res->nbr_ways)
				+ ((float)data->nb_ant / (float)res->nbr_ways)
			> ((float)len / (float)path) + ((float)data->nb_ant / (float)path)))
	{
		res->nbr_ways = path;
		res->total_length = len;
		anthill_cpy(data->ant_hill, data->ant_cpy);
		return (1);
	}
	return (0);
}

int		sv_try_way(t_data *data, t_ant *node, int len, int path)
{
	int		i;

	len++;
	node->path = path;
	if (node->hot == 1)
	{
		path++;
		save_res(data, data->res, len, path);
		sv_redirect_way(data, len, path);
	}
	else if ((i = get_min_hot(node)) != -1)
		sv_try_way(data, node->chd[i], len, path);
	node->path = -1;
	return (0);
}

int		sv_redirect_way(t_data *data, int len, int path)
{
	int		i;

	if (!apply_new_hot(data))
		return (0);
	if ((i = get_min_hot(data->start)) != -1)
		sv_try_way(data, data->start->chd[i], len, path);
	return (0);
}

int		sv_choose_way(t_data *data, int len, int path)
{
	int		i;

	i = -1;
	while (data->start->chd && data->start->chd[++i])
	{
		apply_new_hot(data);
		if (data->start->chd[i]->hot > 0)
			sv_try_way(data, data->start->chd[i], len, path);
	}
	return (0);
}

int		sv_main(t_data *data)
{
	t_res	res;
	int		len;
	int		path;

	data->ant_cpy = anthill_dup(data->ant_hill);
	res.nbr_ways = 0;
	res.total_length = 0;
	res.way = NULL;
	data->res = &res;
	len = 0;
	path = 0;
	sv_choose_way(data, len, path);
	anthill_cpy(data->ant_cpy, data->ant_hill);
	new_hot(data, res);
	sv_send(data, res);
	free_ant_cpy(data->ant_cpy);
	return (1);
}
