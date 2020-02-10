/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pr_utils.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 11:49:44 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/18 11:50:01 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/header.h"

int		pr_get_line_len(char *line)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if ((ft_isdigit(line[i]) || line[i] == '-') && (++i))
		{
			len++;
			while (ft_isdigit(line[i]))
				i++;
		}
		else if (line[i])
			return (0);
	}
	return (len);
}

int		*pr_get_line_int(char *line, int len)
{
	int	i;
	int	*array;
	int	a;

	a = -1;
	i = 0;
	if (!(array = ft_memalloc(sizeof(int) * len)))
		return (NULL);
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if ((ft_isdigit(line[i]) || line[i] == '-') && (++i))
		{
			array[++a] = ft_atoi(&line[i - 1]);
			while (ft_isdigit(line[i]))
				i++;
		}
	}
	return (array);
}
