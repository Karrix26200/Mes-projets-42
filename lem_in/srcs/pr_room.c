/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pr_room.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tvarnier <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/17 10:24:41 by tvarnier     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 17:20:18 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		pr_ant_values(t_ant *ant, char *line, int hot, int i)
{
	ant->x = ft_atoi(&line[i]);
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (!ft_is_number(&line[i]))
	{
		pr_clear_ant(ant);
		return (0);
	}
	ant->y = ft_atoi(&line[i]);
	ant->hot = hot;
	ant->ant = NO_ANT;
	ant->next = NULL;
	ant->path = -1;
	return (1);
}

t_ant	*pr_try_parse_room(char *line, int hot, t_data *d)
{
	int		i;
	t_ant	*ant;

	if (ft_count_words(line, ' ') != 3 || !(ant = ft_memalloc(sizeof(t_ant))))
		return (NULL);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (pr_clear_ant(ant));
	ant->name = ft_strsub(line, i, ft_strindex(&(line[i]), ' '));
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (!ft_is_number(&line[i]) || ant->name[0] == 'L'
			|| ft_strchr(ant->name, '-'))
		return (pr_clear_ant(ant));
	if (!(pr_ant_values(ant, line, hot, i)))
		return (NULL);
	if (hot == END)
		d->end = ant;
	else if (hot == START)
		d->start = ant;
	return (ant);
}

int		pr_is_room_unique(t_ant *new_ant, t_ant *begin, t_ant **tmp)
{
	while (begin)
	{
		if (!ft_strcmp(new_ant->name, begin->name)
				|| (new_ant->x == begin->x && new_ant->y == begin->y))
		{
			new_ant = pr_clear_ant(new_ant);
			return (1);
		}
		*tmp = begin;
		begin = begin->next;
	}
	return (0);
}

int		pr_is_valid_room(char **line, t_data *d)
{
	t_ant	*new_ant;
	t_ant	*begin;
	t_ant	*tmp;
	int		hot;

	begin = d->ant_hill;
	tmp = begin;
	if ((hot = pr_is_valid_comment(line, d)) == 1 || hot == -3)
		return (hot == -3 ? 0 : 1);
	if (ft_strchr(*line, '-') && !ft_strchr(*line, ' '))
		return (-1);
	if (!(new_ant = pr_try_parse_room(*line, hot, d)))
		return (1);
	if (pr_is_room_unique(new_ant, begin, &tmp))
		return (1);
	d->final_str = ft_strjoin_del(d->final_str,
			ft_strjoin_del(*line, ft_strdup("\n")));
	if (!d->ant_hill)
		d->ant_hill = new_ant;
	else
		tmp->next = new_ant;
	return (0);
}

int		pr_room_parse(t_data *d, char **line)
{
	int		ret_room;

	d->ant_hill = NULL;
	d->ant_cpy = NULL;
	while (get_next_line(0, line) == 1)
	{
		if (ft_strlen(*line) == 0)
			return (0);
		*line = ft_strrep(*line, ft_rm_space(*line));
		if ((ret_room = pr_is_valid_room(line, d)) == 1)
			break ;
		else if (ret_room == -1)
			return (0);
	}
	ft_strdel(line);
	return (1);
}
