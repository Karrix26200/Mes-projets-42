/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_put_arg.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 10:45:08 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 15:25:57 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int		ft_putreg(char *param, t_data *data)
{
	char	regnb;

	if (param[0] == 'r')
	{
		regnb = ft_atoi(&param[1]);
		if (!data->option)
			write(data->fd, &regnb, 1);
		else
			ft_printf("%-18d", regnb);
	}
	return (1);
}

int		ft_putadd(char *label, t_asm *assemb, t_asm *position, t_data *data)
{
	t_asm			*assemb_temp;
	int				address;
	int				check;
	unsigned char	tmp;
	int				i;

	address = 0;
	assemb_temp = assemb;
	i = 0;
	check = 0;
	address = ft_find_label(assemb, position, &check, label);
	if (check == -1)
		address *= -1;
	tmp = ((address >> 8) & 0xff);
	if (!data->option)
		write(data->fd, &tmp, 1);
	else
		ft_printf("%-4d", tmp);
	tmp = (address & 0xff);
	if (!data->option)
		write(data->fd, &tmp, 1);
	else
		ft_printf("%-4d", tmp);
	return (1);
}

int		ft_putdir(char *param, t_asm *assemb, t_asm *position, t_data *data)
{
	unsigned char	tmp;
	int				dir_size;

	dir_size = ((position->opcode >= 0x09 && position->opcode <= 0x0c)
		|| position->opcode >= 0x0e) ? 2 : 4;
	if (param[0] == DIRECT_CHAR && param[1] != LABEL_CHAR)
		ft_write_dir(param, data->fd, dir_size, data->option);
	else if (!ft_isdigit(param[0]))
	{
		if (dir_size == 4 && !(tmp = 0))
		{
			if (!data->option)
				write(data->fd, &tmp, 1);
			if (!data->option)
				write(data->fd, &tmp, 1);
			else
				ft_printf("%-4d%-4d", tmp, tmp);
		}
		ft_putadd(param, assemb, position, data);
	}
	else
		ft_write_else(param, data->fd, data->option);
	if (data->option)
		ft_printf(dir_size == 4 ? "  " : "          ");
	return (1);
}

int		ft_putind(char *param, t_asm *assemb, t_asm *position, t_data *data)
{
	int				ind;
	t_asm			*assemb_temp;
	unsigned char	tmp;

	assemb_temp = NULL;
	if (param[0] != DIRECT_CHAR && param[0] != LABEL_CHAR
		&& (ind = ft_atoi(&param[0])) >= 0)
	{
		tmp = ind >> 8;
		ind &= 255;
		if (!data->option)
		{
			write(data->fd, &tmp, 1);
			write(data->fd, &ind, 1);
		}
		else
			ft_printf("%-4d%-4d", tmp, ind);
	}
	else if (param[0] != DIRECT_CHAR && param[0] != LABEL_CHAR)
		write_neg_ind(ind, data);
	else
		ft_putadd(param, assemb, position, data);
	if (data->option)
		ft_printf("%10c", ' ');
	return (1);
}

char	**check_label_chars(char *label, int *j)
{
	int		i;

	i = 0;
	*j = 0;
	while (label[i])
	{
		if (!ft_strchr(LABEL_CHARS, label[i]))
			return (NULL);
		i++;
	}
	return (ft_strsplit(label, SEPARATOR_CHAR));
}
