/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_get.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sbedene <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/13 12:04:31 by sbedene      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 14:04:51 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

char	*ft_get_champ_name(char *buff)
{
	int		i;
	int		j;
	char	*name;

	i = 3;
	if (buff[0] != (char)((COREWAR_EXEC_MAGIC >> 24) & 0xFF)
		|| buff[1] != (char)((COREWAR_EXEC_MAGIC >> 16) & 0xFF)
			|| buff[2] != (char)((COREWAR_EXEC_MAGIC >> 8) & 0xFF)
				|| buff[3] != (char)(COREWAR_EXEC_MAGIC & 0xFF))
		return (NULL);
	j = 1;
	while (buff[i + j])
		j++;
	if (!(name = (char *)malloc(j * sizeof(char))))
		return (NULL);
	j = 0;
	while (buff[++i])
		name[j++] = buff[i];
	name[j] = '\0';
	return (name);
}

char	*ft_get_champ_comment(char *buff, int size)
{
	int		i;
	int		j;
	char	*comment;

	i = 0;
	while (++i < CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
		if ((((buff[i - 1] << 8) & 0xff00) | (buff[i] & 0xff)) == size)
			break ;
	j = 1;
	while (buff[i + j])
		j++;
	if (j == 1)
		return (ft_strdup(""));
	if (!(comment = (char *)malloc(j * sizeof(char))))
		return (NULL);
	j = 0;
	while (buff[++i])
		comment[j++] = buff[i];
	comment[j] = '\0';
	return (comment);
}

char	*ft_get_bin(int fd, int *size, char *chmp, t_player *player)
{
	char		buff[CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 16];
	char		*bin;
	int			ret;
	int			mor;
	char		buffmore[10000];

	ret = read(fd, &buff,
			CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 16);
	if ((mor = read(fd, &buffmore, 10000)) > 0)
	{
		ft_fdprintf(2,
			"Error: File %s has too large a code (%d bytes > %d bytes)\n", chmp,
			ret + mor - PROG_NAME_LENGTH - COMMENT_LENGTH - 16, CHAMP_MAX_SIZE);
		return (NULL);
	}
	if ((is_invalid_magic(buff, chmp) || is_invalid_size(ret -
		(PROG_NAME_LENGTH + COMMENT_LENGTH + 16), (unsigned char *)buff, chmp)
			|| !(bin = (char *)malloc((ret) * sizeof(char)))))
		return (NULL);
	ft_memcpy(bin, buff, ret);
	*size = ret;
	player->prog_size = ret - (PROG_NAME_LENGTH + COMMENT_LENGTH + 16);
	player->name = ft_get_champ_name(buff);
	player->comment = ft_get_champ_comment(buff, player->prog_size);
	return (bin);
}

char	*ft_get_hex(int i, int len)
{
	char	*res;

	if (i / 4096 > 0)
		return (res = ft_baseconvert("0123456789abcdef", i));
	else if (i / 256 > 0)
		return (res = ft_strfjoin(ft_strfillnew('0', 1),
			ft_baseconvert("0123456789abcdef", i)));
	else if ((unsigned char)i / 16 > 0)
		return (res = ft_strfjoin(len == 4
			? ft_strfillnew('0', 2) : ft_strdup(""),
				ft_baseconvert("0123456789abcdef", (unsigned char)i)));
	else
	{
		return (ft_strfjoin(ft_strfillnew('0', len == 4 ? 3 : 1),
			ft_baseconvert("0123456789abcdef", (unsigned char)i)));
	}
	return (NULL);
}

char	*ft_get_color(int player, t_mem *mem, t_process *process)
{
	int		check;

	if (COLOR)
	{
		check = 0;
		while (process)
		{
			if (process->mem == mem && (check = 1))
				break ;
			process = process->next;
		}
		if (player == 0)
			return (ft_strdup(check == 0 ? BLUE : BBLUE));
		else if (player == 1)
			return (ft_strdup(check == 0 ? RED : BRED));
		else if (player == 2)
			return (ft_strdup(check == 0 ? GREEN : BGREEN));
		else if (player == 3)
			return (ft_strdup(check == 0 ? YELLOW : BYELLOW));
		else
			return (ft_strdup(check == 0 ? NONE : BNONE));
	}
	return (NULL);
}
