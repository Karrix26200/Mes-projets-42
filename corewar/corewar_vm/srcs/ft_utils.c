/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_utils.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 20:12:19 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 20:14:43 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		ft_ispath(char *champion)
{
	int		fd;
	char	*tmp;

	fd = -1;
	tmp = NULL;
	if (ft_strlen(champion) > 4 && !ft_strcmp((tmp = ft_strsub(champion,
						ft_strlen(champion) - 4, ft_strlen(champion))), ".cor"))
		fd = open(champion, O_RDONLY);
	ft_strdel(&tmp);
	return (fd > 0 ? fd : 0);
}

int		get_opsize(int nb, int dir_size)
{
	if (nb == REG_CODE)
		return (1);
	if (nb == DIR_CODE)
		return (dir_size);
	if (nb == IND_CODE)
		return (2);
	return (0);
}

int		is_invalid_magic(char *buff, char *champ)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (buff[i] != (char)((COREWAR_EXEC_MAGIC >> (8 * (3 - i)) & 0xff)))
			return (ft_fdprintf(2, "Error: File %s %s", champ, MAGIC_ERR));
		i++;
	}
	return (0);
}

int		is_invalid_size(int size, unsigned char *buff, char *champ)
{
	if (((buff[0x8a] << 8) + buff[0x8b]) != size)
		return (ft_fdprintf(2, "Error: File %s %s", champ, SIZE_ERR));
	return (0);
}
