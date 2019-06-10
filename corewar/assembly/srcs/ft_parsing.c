/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sbedene <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/10 20:56:41 by sbedene      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 08:41:55 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

t_asm	*init_instr(void)
{
	t_asm	*instr;

	if (!(instr = (t_asm *)malloc(sizeof(t_asm))))
		return (NULL);
	instr->label = NULL;
	instr->params = NULL;
	instr->instruction = NULL;
	instr->size = 0;
	instr->param_code = 0;
	instr->next = NULL;
	return (instr);
}

int		new_clean_line(t_data *data, int *tmp)
{
	char	*cpy;

	ft_strdel(&data->line);
	get_next_line(data->fd, &data->line);
	if (!(data->line))
		return (0);
	if ((*tmp = ft_strichr(data->line, COMMENT_CHAR)) != -1)
	{
		cpy = data->line;
		data->line = ft_strsub(cpy, 0, *tmp - 1);
		ft_strdel(&cpy);
	}
	if ((*tmp = ft_strichr(data->line, ';')) != -1)
	{
		cpy = data->line;
		data->line = ft_strsub(cpy, 0, *tmp);
		ft_strdel(&cpy);
	}
	return (1);
}

t_asm	*new_instr(t_data *data, char **i_lst, unsigned int *prog_size)
{
	t_asm	*instr;
	int		i;
	int		tmp;

	if (!(instr = init_instr()))
		return (NULL);
	add_label(instr, data, &tmp, &i);
	while (((!data->line[i]) || data->line[i] == COMMENT_CHAR
		|| data->line[i] == ';') && ++data->nb)
	{
		if (!new_clean_line(data, &tmp))
			break ;
		add_label(instr, data, &tmp, &i);
	}
	if (!(add_instr_val(instr, data, &i))
		|| !(check_instruction(instr, data, i_lst, prog_size)))
		return (free_instr(instr));
	return (instr);
}

int		ft_get_instruction(t_asm **instr, t_data *data, unsigned int *prog_size)
{
	char	**i_lst;
	t_asm	*curr;

	i_lst = ft_init_instruction_list();
	curr = NULL;
	while (data->line)
	{
		if (is_valid_instruction(data->line) == 1)
		{
			if ((!*instr && !(*instr = new_instr(data, i_lst, prog_size)))
				|| (curr && !(curr->next = new_instr(data, i_lst, prog_size))))
				return (free_lst(instr, i_lst));
			curr = ((*instr)->next ? curr->next : *instr);
		}
		else if (is_valid_instruction(data->line) == -1)
			return (check_unexpected_cmd(data, i_lst));
		ft_strdel(&data->line);
		get_next_line(data->fd, &data->line);
		data->nb++;
	}
	free_tab(i_lst);
	curr->next = *instr;
	return (1);
}
