/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pr_main.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tvarnier <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/17 09:19:52 by tvarnier     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 17:13:42 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			ft_is_number(char *str)
{
	int		i;

	i = -1;
	while (str[++i] && str[i] != ' ')
	{
		if (!ft_isdigit(str[i]) || i > 9)
			return (0);
	}
	return (1);
}

int			pr_start_end(char **line, t_data *d, int *hot, int s_e)
{
	d->final_str = ft_strjoin_del(d->final_str,
		ft_strjoin_del(ft_strdup(*line), ft_strdup("\n")));
	if (s_e == START && (d->start || *hot != -2))
		return (1);
	else if (s_e == END && (d->end || *hot != -2))
		return (1);
	*hot = s_e;
	return (0);
}

int			pr_is_valid_comment(char **line, t_data *d)
{
	int		hot;

	hot = -2;
	while (1)
	{
		if (!ft_strcmp(*line, "##start") && pr_start_end(line, d, &hot, START))
			return (1);
		else if (!ft_strcmp(*line, "##end") && pr_start_end(line, d, &hot, END))
			return (1);
		else if (*line[0] != '#')
			return (hot);
		ft_strdel(line);
		if (get_next_line(0, line) != 1)
		{
			if (hot == START || hot == END)
				return (1);
			else
				return (-3);
		}
	}
}

int			pr_ant_parse(t_data *d)
{
	char	*l;
	int		i;

	l = NULL;
	if (get_next_line(0, &l) != 1)
		return (ft_strdel_ret(&l));
	else
	{
		i = -1;
		while (l[++i])
			if (!ft_isdigit(l[i]))
				return (ft_strdel_ret(&l));
		if (i == 0)
			return (ft_strdel_ret(&l));
	}
	d->nb_ant = ft_atol(l);
	d->final_str = ft_strjoin_del(d->final_str,
			ft_strjoin_del(l, ft_strdup("\n")));
	return (0);
}

t_data		*pr_main(void)
{
	t_data	*d;
	char	*line;

	if (!(d = ft_memalloc(sizeof(t_data))))
		return (NULL);
	d->final_str = ft_strnew(0);
	line = NULL;
	if (pr_ant_parse(d) || pr_room_parse(d, &line) || pr_tube_parse(d, line))
		return (pr_free_all(d));
	return (d);
}
