/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   anthill.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tvarnier <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/17 08:48:50 by tvarnier     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/10 17:02:24 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		pr_link_start(t_ant *begin)
{
	int		i;

	i = -1;
	while (begin->chd && begin->chd[++i])
		if (begin->chd[i]->hot == START)
			return (2);
	return (1);
}

int		pr_backtrack_heat(t_ant *begin, int tier, int target)
{
	int		i;
	int		tmp;
	int		ret;

	i = -1;
	if (tier < target)
	{
		tmp = 0;
		while (begin->chd && begin->chd[++i])
			if (begin->chd[i]->path == -1
					&& (begin->chd[i]->hot == tier + 1
						|| begin->chd[i]->hot == -2)
				&& (ret = pr_backtrack_heat(begin->chd[i], tier + 1, target)))
				tmp = (ret > tmp) ? ret : tmp;
		return (tmp);
	}
	else if (tier == target && begin->hot == -2)
	{
		begin->hot = tier;
		return (pr_link_start(begin));
	}
	return (0);
}
