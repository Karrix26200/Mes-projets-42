/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parseutils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sbedene <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/13 16:16:30 by sbedene      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 15:25:55 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

char	get_opcode(char *instr, char **i_lst)
{
	int		i;

	i = 0;
	while (i_lst[i])
		if (!ft_strcmp(instr, i_lst[i++]))
			return ((char)i);
	return (0);
}

int		is_valid_instruction(char *line)
{
	int		i;
	int		check;

	check = 0;
	i = 0;
	if (line[i] == '.')
		return (-1);
	if (line[i] == COMMENT_CHAR || line[i] == ';' || !line[i])
		return (0);
	while (line[i])
	{
		if (!ft_isspace(line[i]) && line[i] != COMMENT_CHAR && line[i] != ';')
			return (1);
		else if (line[i] == COMMENT_CHAR || line[i] == ';')
			return (0);
		i++;
	}
	return (check);
}

char	get_param_code(char **params, size_t *size,
		int opcode, unsigned int *prog_size)
{
	int		i;
	char	param_code;

	param_code = 0;
	i = 0;
	if (opcode == 0x0c || opcode == 0x01 || opcode == 0x09 || opcode == 0x0f)
		(*size)--;
	while (params[i])
	{
		if (params[i][0] == 'r' && (*size)++)
			param_code += (REG_CODE << (8 - (i + 1) * 2));
		else if (params[i][0] == DIRECT_CHAR && ((*size) += opcode == 1
			|| opcode == 2 || opcode == 6 || opcode == 7
				|| opcode == 8 || opcode == 13 ? 4 : 2))
			param_code += (DIR_CODE << (8 - (i + 1) * 2));
		else if ((*size) += 2)
			param_code += (IND_CODE << (8 - (i + 1) * 2));
		i++;
	}
	*prog_size += *size;
	return (param_code);
}

int		check_label(t_asm *assemb, t_asm *first, char *label)
{
	char	**tab;
	int		i;
	int		j;

	while (assemb)
	{
		if (assemb->label && !(i = 0))
		{
			if (!(tab = check_label_chars(assemb->label, &j)))
				return (1);
			while (tab && tab[i])
				if (!ft_strcmp(tab[i++], label))
				{
					while (tab[j])
						ft_strdel(&tab[j++]);
					free(tab);
					return (1);
				}
			while (tab[j])
				ft_strdel(&tab[j++]);
			free(tab);
		}
		assemb = assemb->next == first ? NULL : assemb->next;
	}
	return (0);
}

int		ft_check_labels(t_asm *assemb, t_asm *first)
{
	int		i;

	while (assemb)
	{
		i = 0;
		while (assemb->instruction && assemb->params[i])
		{
			if ((assemb->params[i][0] == LABEL_CHAR
				&& !check_label(first, first, &(assemb->params[i][1])))
					|| (assemb->params[i][1] == LABEL_CHAR
						&& !check_label(first, first, &(assemb->params[i][2]))))
			{
				ft_fdprintf(2, "Undefined label at instruction %s : %s\n",
					assemb->instruction, assemb->params[i]);
				return (0);
			}
			i++;
		}
		assemb = assemb->next == first ? NULL : assemb->next;
	}
	return (1);
}
