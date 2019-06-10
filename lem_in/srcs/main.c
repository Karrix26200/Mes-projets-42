/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tvarnier <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/17 08:47:57 by tvarnier     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 16:09:39 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		pr_heatmap(t_data *d)
{
	int		max_heat;
	int		i;
	int		tmp;
	int		ret;

	d->start->ant = d->nb_ant;
	i = 1;
	tmp = (pr_link_start(d->end) == 2) ? 2 : 0;
	while ((ret = pr_backtrack_heat(d->end, 0, i)))
	{
		tmp = (ret > tmp) ? ret : tmp;
		i++;
	}
	if (tmp != 2)
		return (0);
	max_heat = i;
	ft_putendl(d->final_str);
	sv_main(d);
	return (1);
}

int		main(void)
{
	t_data *d;

	if (!(d = pr_main()))
		ft_putstr("ERROR\n");
	else
	{
		if (!(pr_heatmap(d)))
			ft_putstr("ERROR\n");
		pr_free_all(d);
	}
	return (0);
}
