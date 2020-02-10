/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_param.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 08:29:03 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 13:03:20 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int		is_wrong_instr(char *instr, char **params, int opcode, int l)
{
	if (wrong_nb_param(opcode, params))
		return (ft_fdprintf(2, "%s%s line %d\n", WARG, instr, l));
	if ((opcode == 0x01 || opcode == 0x09 || opcode == 0x0c
		|| opcode == 0x0f) && !is_direct(params[0]))
		return (ft_fdprintf(2, "%s%s line %d\n", WPRM, instr, l));
	if ((opcode == 0x02 || opcode == 0x0d)
		&& (is_registre(params[0]) || !is_registre(params[1])))
		return (ft_fdprintf(2, "%s%s line %d\n", WPRM, instr, l));
	if (opcode == 0x03 && (!is_registre(params[0]) || is_direct(params[1])))
		return (ft_fdprintf(2, "%s%s line %d\n", WPRM, instr, l));
	if ((opcode == 0x04 || opcode == 0x05) && (!is_registre(params[0])
		|| !is_registre(params[1]) || !is_registre(params[2])))
		return (ft_fdprintf(2, "%s%s line %d\n", WPRM, instr, l));
	if ((opcode == 0x06 || opcode == 0x07
		|| opcode == 0x08) && !is_registre(params[2]))
		return (ft_fdprintf(2, "%s%s line %d\n", WPRM, instr, l));
	if ((opcode == 0x0a || opcode == 0x0e)
		&& (is_indirect(params[1]) || !is_registre(params[2])))
		return (ft_fdprintf(2, "%s%s line %d\n", WPRM, instr, l));
	if (opcode == 0x0b && (!is_registre(params[0]) || is_indirect(params[2])))
		return (ft_fdprintf(2, "%s%s line %d\n", WPRM, instr, l));
	if (opcode == 0x10 && !is_registre(params[0]))
		return (ft_fdprintf(2, "%s%s line %d\n", WPRM, instr, l));
	return (0);
}

int		is_invalidparam(char *param)
{
	int		i;

	i = 0;
	if ((param[i] == DIRECT_CHAR && !ft_isalnum(param[i + 1])
		&& param[i + 1] != LABEL_CHAR && param[i + 1] != '-') || !param[i])
		return (1);
	return (0);
}

char	**split_params(char *line)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	**params;

	tmp = NULL;
	tmp2 = NULL;
	if ((j = ft_strichr(line, COMMENT_CHAR)) != -1)
		tmp = ft_strsub(line, 0, j);
	if ((j = ft_strichr(tmp ? tmp : line, ';')) != -1)
		tmp2 = ft_strsub(tmp ? tmp : line, 0, j);
	if (!tmp2)
		tmp2 = tmp ? tmp : line;
	if (line[ft_strlen(tmp2) - 1] == SEPARATOR_CHAR)
	{
		if (tmp2 != line && tmp2 != tmp)
			ft_strdel(&tmp2);
		ft_strdel(&tmp);
		return (NULL);
	}
	params = ft_strsplit(tmp2, SEPARATOR_CHAR);
	if (tmp2 != line && tmp2 != tmp)
		ft_strdel(&tmp2);
	ft_strdel(&tmp);
	return (params);
}

int		check_param(char **params, int i, int j)
{
	char	*tmp;

	tmp = ft_strsub(params[i], 0, j);
	while (ft_isspace(params[i][j]))
		j++;
	if ((params[i][j] && params[i][j] != COMMENT_CHAR))
	{
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&params[i]);
	params[i] = tmp;
	return (1);
}

char	**get_params(char *line)
{
	char	**params;
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	params = split_params(line);
	while (params && params[++i])
	{
		j = 0;
		tmp = ft_strtrim(params[i]);
		ft_strdel(&params[i]);
		params[i] = tmp;
		if (is_invalidparam(params[i]))
			return (free_tab(params));
		while (params[i][j] && !ft_isspace(params[i][j]))
			j++;
		if (params[i][j] && !check_param(params, i, j))
			return (free_tab(params));
	}
	return (!params || i == 0 ? free_tab(params) : params);
}
