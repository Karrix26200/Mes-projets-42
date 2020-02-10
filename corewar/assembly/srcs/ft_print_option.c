/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print_option.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 11:51:15 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 13:11:36 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

void	ft_print_option(t_asm *list, int *bit)
{
	int		i;

	i = 0;
	if (list->label)
		ft_print_label(list->label, *bit);
	if (list->size)
	{
		ft_printf("%-5d(%-3d) :        %-10s",
			*bit, list->size, list->instruction);
		while (list->params[i])
			ft_printf("%-18s", list->params[i++]);
		ft_printf("\n%20c%-4d", ' ', list->opcode);
		*bit += list->size;
	}
}

void	ft_write_addr_option(t_asm *list, t_asm *assemb, int i, int *check)
{
	int		address;

	*check = 0;
	if (list->params[i][0] == LABEL_CHAR
		|| (list->params[i][1] == LABEL_CHAR
			&& list->params[i][0] == DIRECT_CHAR))
	{
		address = ft_find_label(assemb, list, check, list->params[i]);
		ft_printf("%-18d", *check == -1 ? -address : address);
	}
	else
		ft_printf("%-18d", ft_atoll(&(list->params[i][list->params[i][0]
			== DIRECT_CHAR ? 1 : 0])));
}

void	ft_write_synth_option(t_asm *list, t_asm *assemb)
{
	int		i;
	int		opc;
	int		check;

	i = 0;
	ft_printf("%20c%-4d", ' ', list->opcode);
	if (list->opcode != 0x0c && list->opcode != 0x09
		&& list->opcode != 0x01 && list->opcode != 0x0f)
		ft_printf("%-6d", (unsigned char)list->param_code);
	else
		ft_printf("      ");
	opc = list->param_code;
	while (opc)
	{
		if ((opc & 0xc0) == (REG_CODE << 6))
			ft_printf("%-18d", ft_atoi(&list->params[i][1]));
		else if ((opc & 0xc0) == (DIR_CODE << 6)
			|| (opc & 0xc0) == (IND_CODE << 6))
			ft_write_addr_option(list, assemb, i, &check);
		i++;
		opc = opc << 2;
	}
	ft_printf("\n\n");
}

void	ft_option_pres(char *name, char *comm, int size)
{
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", size);
	ft_printf("Name : \"%s\"\nComment : \"%s\"\n\n", name, comm);
}

void	print_argument(t_asm *tmp, t_data *data, t_asm *assemb)
{
	char	bin;

	if (tmp->opcode != 0x0c && tmp->opcode != 0x09
		&& tmp->opcode != 0x01 && tmp->opcode != 0x0f)
	{
		bin = tmp->param_code;
		if (data->option == 0)
			write(data->fd, &bin, 1);
		else if (tmp->size)
			ft_printf("%-6d", (unsigned char)bin);
	}
	else if (data->option && tmp->size)
		ft_printf("      ");
	ft_write_params(tmp, assemb, data);
	if (data->option && tmp->size)
		ft_write_synth_option(tmp, assemb);
}
