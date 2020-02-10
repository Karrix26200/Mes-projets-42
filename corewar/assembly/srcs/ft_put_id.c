/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_put_id.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 11:45:58 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 13:21:06 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/asm.h"

int		ft_putname(char *name, int fd)
{
	char	*tmp;
	int		len;

	len = ft_strlen(name);
	tmp = ft_strnew(PROG_NAME_LENGTH - len + 1);
	tmp[0] = (char)((COREWAR_EXEC_MAGIC >> 24) & 0xff);
	write(fd, &tmp[0], 1);
	tmp[0] = (char)((COREWAR_EXEC_MAGIC >> 16) & 0xff);
	write(fd, &tmp[0], 1);
	tmp[0] = (char)((COREWAR_EXEC_MAGIC >> 8) & 0xff);
	write(fd, &tmp[0], 1);
	tmp[0] = (char)((COREWAR_EXEC_MAGIC) & 0xff);
	write(fd, &tmp[0], 1);
	tmp[0] = 0;
	write(fd, name, len);
	write(fd, tmp, PROG_NAME_LENGTH - len);
	ft_strdel(&tmp);
	return (1);
}

int		ft_putcomment(char *name, int size, int fd)
{
	char			*tmp;
	unsigned char	comment_size;
	int				len;

	len = ft_strlen(name);
	tmp = ft_strnew(COMMENT_LENGTH - len + 7);
	write(fd, tmp, 6);
	comment_size = ((size >> 8) & 0xff);
	write(fd, &comment_size, 1);
	comment_size = (size & 0xff);
	write(fd, &comment_size, 1);
	write(fd, name, len);
	write(fd, tmp, COMMENT_LENGTH + 4 - len);
	ft_strdel(&tmp);
	return (1);
}

void	ft_display_id(t_data *data, t_header *id, int *bit)
{
	if (!data->option)
	{
		ft_putname(id->prog_name, data->fd);
		ft_putcomment(id->comment, id->prog_size, data->fd);
	}
	else
		ft_option_pres(id->prog_name, id->comment, id->prog_size);
	*bit = 0;
}
