/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pr_link.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tvarnier <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/17 10:24:31 by tvarnier     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/17 10:27:37 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			pr_get_name(char *line, char **p1, char **p2)
{
	int		i;
	int		a;

	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	a = i;
	while (line[i])
		i++;
	if (!(a > 0 && i - a > 0))
		return (1);
	*p1 = ft_strsub(line, 0, a);
	*p2 = ft_strsub(line, a + 1, i - a - 1);
	if (!ft_strcmp(*p1, *p2))
	{
		ft_strdel(p1);
		ft_strdel(p2);
		return (1);
	}
	return (0);
}

int			pr_try_link(t_ant *t1, t_ant *t2)
{
	int		i;
	int		a;

	i = 0;
	if (t1->chd)
		while (t1->chd[i])
		{
			if (t1->chd[i] == t2)
				return (0);
			i++;
		}
	a = 0;
	if (t2->chd)
		while (t2->chd[a])
		{
			if (t2->chd[a] == t1)
				return (0);
			a++;
		}
	pr_add_chd(t1, t2, i);
	pr_add_chd(t2, t1, a);
	return (0);
}

int			pr_get_link_next(char **p1, char **p2, t_ant *t1, t_ant *t2)
{
	ft_strdel(p1);
	ft_strdel(p2);
	if (!t1 || !t2)
		return (1);
	pr_try_link(t1, t2);
	return (0);
}

int			pr_get_link(t_data *d, char *line)
{
	char	*p1;
	char	*p2;
	t_ant	*t1;
	t_ant	*t2;
	t_ant	*tmp;

	tmp = d->ant_hill;
	p1 = NULL;
	p2 = NULL;
	t1 = NULL;
	t2 = NULL;
	if (pr_get_name(line, &p1, &p2))
		return (1);
	while (tmp)
	{
		if (!ft_strcmp(p1, tmp->name))
			t1 = tmp;
		else if (!ft_strcmp(p2, tmp->name))
			t2 = tmp;
		if (t1 && t2)
			break ;
		tmp = tmp->next;
	}
	return (pr_get_link_next(&p1, &p2, t1, t2));
}

int			pr_tube_parse(t_data *d, char *line)
{
	int		ret;

	if ((ret = 1) == 1 && (!d->start || !d->end))
	{
		ft_strdel(&line);
		return (1);
	}
	while (ret == 1)
	{
		if (line[0] != '#')
		{
			line = ft_strrep(line, ft_rm_space(line));
			d->final_str = ft_strjoin_del(d->final_str,
					ft_strjoin_del(ft_strdup(line), ft_strdup("\n")));
			if (ft_count_words(line, '-') != 2 || pr_get_link(d, line))
			{
				ft_strdel(&line);
				return (1);
			}
		}
		ft_strdel(&line);
		ret = get_next_line(0, &line);
	}
	ft_strdel(&line);
	return (0);
}
