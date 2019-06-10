/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sv_struct.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tvarnier <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/13 15:42:39 by tvarnier     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 15:55:20 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		get_min_hot(t_ant *node)
{
	int		i;
	int		min;
	int		min_index;

	i = -1;
	min = -1;
	min_index = -1;
	while (node->chd && node->chd[++i])
	{
		if (node->chd[i]->hot > 0 && node->chd[i]->path == -1
				&& (min == -1 || node->chd[i]->hot < min))
		{
			min = node->chd[i]->hot;
			min_index = i;
		}
	}
	return (min_index);
}

void	anthill_cpy(t_ant *src, t_ant *dest)
{
	while (src && dest)
	{
		dest->hot = src->hot;
		dest->path = src->path;
		src = src->next;
		dest = dest->next;
	}
}

t_ant	*anthill_dup(t_ant *node)
{
	t_ant	*tmp;

	if (node)
	{
		tmp = NULL;
		if (!(tmp = ft_memalloc(sizeof(t_ant))))
			return (NULL);
		tmp->hot = node->hot;
		tmp->name = node->name;
		tmp->path = node->path;
		tmp->next = anthill_dup(node->next);
		return (tmp);
	}
	return (NULL);
}

void	reset_hot(t_ant *node)
{
	while (node)
	{
		if (node->hot != START && node->hot != END)
			node->hot = -2;
		node = node->next;
	}
}

int		apply_new_hot(t_data *d)
{
	int		i;
	int		tmp;
	int		ret;

	i = 1;
	reset_hot(d->ant_hill);
	tmp = 0;
	while ((ret = pr_backtrack_heat(d->end, 0, i)))
	{
		tmp = (ret > tmp) ? ret : tmp;
		i++;
	}
	if (tmp != 2)
		return (0);
	return (1);
}
