/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_put_arg_utils.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 11:26:12 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 12:03:32 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int		match_label(char *haystack, char *needle, int index)
{
	char	**labels;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(labels = ft_strsplit(haystack, SEPARATOR_CHAR)))
		return (0);
	while (labels && labels[i])
	{
		if (!ft_strcmp(labels[i], &needle[index]))
		{
			while (labels[j])
				ft_strdel(&(labels[j++]));
			free(labels);
			return (1);
		}
		i++;
	}
	while (labels[j])
		ft_strdel(&labels[j++]);
	free(labels);
	return (0);
}

size_t	ft_find_label(t_asm *assemb, t_asm *position, int *check, char *label)
{
	t_asm	*assemb_temp;
	size_t	address;
	int		i;

	i = 0;
	address = 0;
	assemb_temp = assemb;
	while (label[i] == DIRECT_CHAR || label[i] == LABEL_CHAR)
		i++;
	while (assemb_temp)
	{
		if (*check == 0 && assemb_temp == position)
			*check = 1;
		else if (*check == 0 && (assemb_temp->label
			&& match_label(assemb_temp->label, label, i)))
			*check = -1;
		if ((*check == 1 && (assemb_temp->label
			&& match_label(assemb_temp->label, label, i)))
				|| (*check == -1 && assemb_temp == position))
			break ;
		if (*check != 0)
			address += assemb_temp->size;
		assemb_temp = assemb_temp->next == assemb ? NULL : assemb_temp->next;
	}
	return (address);
}

void	ft_write_dir(char *param, int fd, int dir_size, int option)
{
	long			dir;
	int				i;
	unsigned char	tmp;

	dir = ft_atoll(&param[1]);
	if (dir >= 0 && (i = dir_size == 4 ? 24 : 8))
		while (i >= 0)
		{
			tmp = ((dir >> i) & 0xff);
			if (!option)
				write(fd, &tmp, 1);
			else
				ft_printf("%-4d", tmp);
			i -= 8;
		}
	else if ((i = dir_size == 4 ? 24 : 8))
		while (i >= 0)
		{
			tmp = 255 - ((-dir >> i) & 0xff) + (i == 0 ? 1 : 0);
			if (!option)
				write(fd, &tmp, 1);
			else
				ft_printf("%-4d", tmp);
			i -= 8;
		}
}

void	ft_write_else(char *param, int fd, int option)
{
	long			dir;
	unsigned char	tmp;

	dir = ft_atoi(param);
	tmp = dir >> 8;
	if (!option)
	{
		write(fd, &tmp, 1);
		write(fd, &dir, 1);
	}
	else
		ft_printf("%-4d%-4d", tmp, dir);
}

void	write_neg_ind(int ind, t_data *data)
{
	unsigned char	tmp;

	tmp = (USHRT_MAX + ind + 1) >> 8;
	if (!data->option)
		write(data->fd, &tmp, 1);
	else
		ft_printf("%-4d", tmp);
	tmp = ((USHRT_MAX + ind + 1) << 8) >> 8;
	if (!data->option)
		write(data->fd, &tmp, 1);
	else
		ft_printf("%-4d", tmp);
}
