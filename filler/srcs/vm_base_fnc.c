/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_base_fnc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/23 01:49:17 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 02:44:39 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/vm_filler.h"

long		get_microtime(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * (int)1e6 + current_time.tv_usec);
}

void		sleep_calculator(int lagtime)
{
	int sleep;

	sleep = (100000 - (int)(get_microtime() - lagtime)) / 4;
	sleep = sleep < 0 ? 0 : sleep;
	usleep(sleep);
}

int			get_line_length(char *line, int mode)
{
	int i;
	int length;

	i = -1;
	length = 17 + 3;
	mode = mode == 0 ? 4 : 0;
	while (line[++i + mode])
	{
		if (i == 0 || !(i > 0 && line[i + mode] == line[i + mode - 1]))
		{
			if (line[i + mode] == 'X')
				length += 19;
			else if (line[i + mode] == 'x')
				length += 19;
			else if (line[i + mode] == 'O')
				length += 19;
			else if (line[i + mode] == 'o')
				length += 19;
			else
				length += 4;
		}
		length += 2;
	}
	return (length + 6 + 1 + 3 + 6 + 4);
}

void		ft_stradd(char **str, int *x, char *add)
{
	int i;

	i = -1;
	while (add[++i])
		(*str)[(*x)++] = add[i];
}

char		*ft_get_player(char *adr1)
{
	char	*adr2;
	int		len;
	char	*retour;
	char	*line;

	len = 1;
	retour = NULL;
	while (get_next_line(0, &line, 0) == 1)
	{
		if (ft_strncmp(line, "launched", 8) == 0)
		{
			adr1 = ft_strrchr(line, '/') + 1;
			adr2 = adr1;
			while (++adr1 && *adr1 != '.')
				len++;
			retour = ft_strnew(len);
			while (len--)
				retour[len] = adr2[len];
			break ;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (retour);
}
