/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_assembler.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sbedene <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/11 00:28:33 by sbedene      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 12:56:06 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int		ft_create_file(t_asm *assemb, char *name)
{
	int		fd;
	char	*file;

	file = ft_strjoin(name, ".cor");
	if (assemb)
		;
	if (!(fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0000600)))
	{
		ft_strdel(&file);
		return (0);
	}
	ft_strdel(&file);
	return (fd);
}

void	ft_write_params(t_asm *assemb_tmp, t_asm *assemb, t_data *data)
{
	int		i;
	int		opc;

	i = 0;
	opc = assemb_tmp->param_code;
	while (opc)
	{
		if ((opc & (0b11000000)) == (REG_CODE << 6))
			ft_putreg(assemb_tmp->params[i], data);
		else if ((opc & 0b11000000) == (DIR_CODE << 6))
			ft_putdir(assemb_tmp->params[i], assemb, assemb_tmp, data);
		else if ((opc & 0b11000000) == (IND_CODE << 6))
			ft_putind(assemb_tmp->params[i], assemb, assemb_tmp, data);
		i++;
		opc = opc << 2;
	}
	if (data->option)
		ft_printf("\n");
}

void	ft_print_label(char *label, int bit)
{
	char	**lab;
	int		i;

	i = 0;
	lab = ft_strsplit(label, SEPARATOR_CHAR);
	while (lab[i])
	{
		ft_printf("%-11d:    %s:\n", bit, lab[i]);
		ft_strdel(&lab[i++]);
	}
	free(lab);
}

int		ft_create_bin(t_asm *assemb, t_header *id, char *name, t_data *data)
{
	t_asm	*tmp;
	char	bin;
	int		dir_size;
	int		bit;

	if (!(data->fd = ft_create_file(assemb, name)))
		return (0);
	tmp = assemb;
	ft_display_id(data, id, &bit);
	while (tmp)
	{
		dir_size = tmp->size && ((tmp->opcode >= 0x09 && tmp->opcode <= 0x0c)
				|| tmp->opcode >= 0x0e) ? 2 : 4;
		bin = tmp->opcode;
		if (data->option == 0 && tmp->size)
			write(data->fd, &bin, 1);
		else if (data->option)
			ft_print_option(tmp, &bit);
		if (tmp->size)
			print_argument(tmp, data, assemb);
		tmp = tmp->next == assemb ? NULL : tmp->next;
	}
	return (1);
}
