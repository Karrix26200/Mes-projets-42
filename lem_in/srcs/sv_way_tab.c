/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sv_way_tab.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tvarnier <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/13 15:57:25 by tvarnier     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 16:01:14 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	free_tab(int ***tab, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		ft_memdel((void**)&((*tab)[i]));
	ft_memdel((void**)&(*tab));
}

int		**alloc_tab(int size)
{
	int		**tab;
	int		i;

	tab = NULL;
	if (!(tab = (int**)ft_memalloc(sizeof(int*) * (size))))
		return (NULL);
	i = -1;
	while (++i < size)
	{
		tab[i] = NULL;
		if (!(tab[i] = (int*)ft_memalloc(sizeof(int) * (2))))
			return (NULL);
	}
	return (tab);
}

int		get_way_len(t_data *data, int path)
{
	int		i;

	i = -1;
	while (data->start->chd && data->start->chd[++i])
		if (data->start->chd[i]->path == path)
			return (data->start->chd[i]->hot + 1);
	return (0);
}

void	order_ways(int **tab, int len)
{
	int		i;
	int		j;
	int		*tmp;

	i = -1;
	while (++i < len)
	{
		j = i - 1;
		while (++j < len)
			if (tab[i][1] > tab[j][1])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
	}
}

int		**get_way(t_data *data, t_res res)
{
	int		**way;
	int		i;

	way = NULL;
	if (!(way = alloc_tab(res.nbr_ways + res.direct)))
		return (NULL);
	if (res.direct)
	{
		way[0][0] = -1;
		way[0][1] = 1;
	}
	i = -1;
	while (++i < res.nbr_ways)
	{
		way[i + res.direct][0] = i;
		way[i + res.direct][1] = get_way_len(data, i);
	}
	order_ways(way, res.nbr_ways + res.direct);
	return (way);
}
