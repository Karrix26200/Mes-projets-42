/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   struct.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tvarnier <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/17 10:24:49 by tvarnier     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 16:57:52 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		free_ant_cpy(t_ant *ant)
{
	t_ant	*tmp;

	while (ant)
	{
		tmp = ant;
		ant = ant->next;
		ft_memdel((void**)&(tmp));
	}
}

int			pr_add_chd(t_ant *t1, t_ant *t2, int tlen)
{
	t_ant	**new_t1;
	int		i;

	new_t1 = ft_memalloc(sizeof(t_ant*) * (tlen + 2));
	i = 0;
	if (t1->chd)
	{
		while (t1->chd[i])
		{
			new_t1[i] = t1->chd[i];
			i++;
		}
	}
	new_t1[i] = t2;
	ft_memdel((void**)&t1->chd);
	t1->chd = new_t1;
	return (0);
}

t_ant		*pr_clear_ant(t_ant *ant)
{
	ft_strdel(&ant->name);
	ft_memdel((void**)&ant->chd);
	ft_memdel((void**)&ant);
	return (NULL);
}

t_data		*pr_free_all(t_data *d)
{
	t_ant	*tmp;
	t_ant	*begin;

	ft_strdel(&(d->final_str));
	begin = d->ant_hill;
	while (begin)
	{
		tmp = begin;
		begin = begin->next;
		pr_clear_ant(tmp);
	}
	ft_memdel((void**)&d);
	return (NULL);
}

int			ft_strdel_ret(char **l)
{
	ft_strdel(l);
	return (1);
}
