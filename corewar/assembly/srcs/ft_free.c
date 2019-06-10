/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 07:00:07 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 15:37:14 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

void	*free_id(t_header *id)
{
	ft_strdel(&id->prog_name);
	ft_strdel(&id->comment);
	free(id);
	return (0);
}

char	**free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab && tab[i])
		ft_strdel(&(tab[i++]));
	if (tab)
		free(tab);
	return (NULL);
}

void	*free_instr(t_asm *instr)
{
	int		i;

	i = 0;
	ft_strdel(&instr->label);
	ft_strdel(&instr->instruction);
	while (instr->params && instr->params[i])
		ft_strdel(&(instr->params[i++]));
	free(instr->params);
	free(instr);
	return (0);
}

int		free_lst(t_asm **instr, char **lst)
{
	t_asm *tmp;

	while (*instr)
	{
		tmp = ((*instr)->next);
		free_instr((*instr));
		(*instr) = tmp;
	}
	return ((int)free_tab(lst));
}

int		clean_exit(int error, t_data *data, t_asm *assemb, t_header *id)
{
	t_asm	*tmp;
	t_asm	*first;
	char	*cpy;

	first = assemb;
	if (!error && !data->option)
	{
		ft_printf("Writing output to %scor\n", (cpy = ft_strsub(data->file, 0,
			ft_strrchr(data->file, '.') - data->file + 1)));
		ft_strdel(&cpy);
	}
	ft_strdel(&data->line);
	free(data);
	if (id)
		free_id(id);
	while (assemb)
	{
		ft_strdel(&(assemb->label));
		ft_strdel(&(assemb->instruction));
		free_tab(assemb->params);
		tmp = assemb->next == first ? NULL : assemb->next;
		free(assemb);
		assemb = tmp;
	}
	return (error);
}
