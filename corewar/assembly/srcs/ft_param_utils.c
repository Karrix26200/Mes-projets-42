/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_param_utils.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 08:23:14 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 11:36:30 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int		get_param_nb(char **params)
{
	int	i;

	i = 0;
	while (params[i])
		i++;
	return (i);
}

int		is_direct(char *str)
{
	if (str[0] != DIRECT_CHAR)
		return (0);
	return (1);
}

int		is_indirect(char *str)
{
	if (str[0] == DIRECT_CHAR || str[0] == 'r')
		return (0);
	return (1);
}

int		is_registre(char *str)
{
	int		reg;

	reg = ft_atoi(&str[1]);
	if (str[0] != 'r' || reg > 99 || reg < 0)
		return (0);
	return (1);
}

int		wrong_nb_param(int opcode, char **params)
{
	int		arg_nb;

	arg_nb = get_param_nb(params);
	if ((arg_nb == 1 && opcode != 0x01 && opcode != 0x09 && opcode != 0x0c
		&& opcode != 0x0f && opcode != 0x10) || (arg_nb == 2
			&& opcode != 0x02 && opcode != 0x03 && opcode != 0x0d)
				|| (arg_nb == 3 && opcode != 0x04 && opcode != 0x05
					&& opcode != 0x06 && opcode != 0x07 && opcode != 0x08
						&& opcode != 0x0a && opcode != 0x0b && opcode != 0x0e)
							|| (arg_nb > 3))
		return (1);
	return (0);
}
