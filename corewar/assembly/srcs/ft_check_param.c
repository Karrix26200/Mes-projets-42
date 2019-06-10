/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check_param.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 08:36:36 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 08:41:16 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int		is_label(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != LABEL_CHAR && (ft_strchr(LABEL_CHARS, str[i])))
		i++;
	if (str[i] != LABEL_CHAR)
		return (0);
	return (1);
}

void	add_label(t_asm *instr, t_data *data, int *tmp, int *i)
{
	*i = 0;
	*tmp = 0;
	while (data->line[*i] && ft_isspace(data->line[*i]))
		(*i)++;
	if (*i == 0 && (is_label(data->line)))
	{
		if (instr->label)
			instr->label = ft_strfjoin(instr->label,
				ft_strfjoin(ft_strfillnew(SEPARATOR_CHAR, 1),
					ft_strsub(data->line, 0,
						(*tmp = ft_strichr(data->line, LABEL_CHAR)))));
		else
			instr->label = ft_strsub(data->line, 0,
				*tmp = ft_strichr(data->line, LABEL_CHAR));
	}
	*i += *tmp == 0 ? 0 : *tmp + 1;
	while (data->line[*i] && ft_isspace(data->line[*i]))
		(*i)++;
}

int		add_instr_val(t_asm *instr, t_data *data, int *i)
{
	int		j;

	while (data->line && data->line[*i] && ft_isspace(data->line[*i]))
		(*i)++;
	j = *i;
	while (data->line && data->line[j]
		&& !ft_isspace(data->line[j]) && ft_isalpha(data->line[j]))
		j++;
	instr->instruction = data->line
		? ft_strsub(&data->line[*i], 0, j - *i) : NULL;
	if ((data->line && !(instr->params = get_params(&data->line[j]))))
	{
		ft_fdprintf(2, "Wrong parameters at Line %d\n", data->nb);
		return (0);
	}
	return (1);
}

int		check_instruction(t_asm *instr, t_data *data,
		char **i_lst, unsigned int *prog_size)
{
	if (data->line && !(instr->opcode = get_opcode(instr->instruction, i_lst)))
	{
		ft_fdprintf(2, "Wrong instruction at Line %d\n", data->nb);
		return (0);
	}
	if (data->line && is_wrong_instr(instr->instruction,
		instr->params, instr->opcode, data->nb))
		return (0);
	instr->size = data->line ? 2 : 0;
	instr->param_code = data->line
		? get_param_code(instr->params, &(instr->size),
			instr->opcode, prog_size) : 0;
	return (1);
}

int		check_unexpected_cmd(t_data *data, char **i_lst)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->line[i] && !ft_isspace(data->line[i]))
		i++;
	ft_fdprintf(2, "Unexpected command string \"%s\" at Line %d\n",
		(tmp = ft_strsub(data->line, 0, i)), &data->nb);
	ft_strdel(&tmp);
	return ((int)free_tab(i_lst));
}
