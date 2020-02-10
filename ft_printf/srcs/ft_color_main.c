/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_color_main.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/02 04:15:40 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/02 04:32:36 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_get_color_id_other(const char *format, int *i, int a)
{
	int ret;

	ret = -1;
	if (a > 4)
		ret = -1;
	else if (ft_strncmp(&format[*i], "OBLD", 4) == 0)
		ret = 1;
	else if (ft_strncmp(&format[*i], "OUDL", 4) == 0)
		ret = 4;
	else if (ft_strncmp(&format[*i], "OITA", 4) == 0)
		ret = 3;
	else if (a > 3)
		ret = -1;
	else if (ft_strncmp(&format[*i], "EOA", 3) == 0)
		ret = 0;
	else if (ft_strncmp(&format[*i], "EOB", 3) == 0)
		ret = 49;
	else if (ft_strncmp(&format[*i], "EOF", 3) == 0)
		ret = 39;
	if (ret != -1)
		*i = *i + a;
	return (ret);
}

int			ft_get_color_txt(const char *format)
{
	char	*str;
	int		i;

	str = "GRYREDGRNYELBLUMAGCYAWHT";
	i = 0;
	while (str[i])
	{
		if (ft_strncmp(format, &str[i], 3) == 0)
			return (i / 3);
		i += 3;
	}
	return (-1);
}

int			ft_get_color_id_macro(const char *format, int *i, int a)
{
	int		colorint;
	int		sideint;

	if (format[*i] == '*')
	{
		if (ft_strindex("BF", format[*i + 1]) == -1 || a != 5)
			return (-1);
		sideint = format[*i + 1] == 'B' ? 100 : 90;
		if ((colorint = ft_get_color_txt(&format[*i + 2])) == -1)
			return (-1);
		*i = *i + a;
		return (sideint + colorint);
	}
	else if (format[*i] == 'B' || format[*i] == 'F')
	{
		if (a != 4)
			return (-1);
		sideint = format[*i] == 'B' ? 40 : 30;
		if ((colorint = ft_get_color_txt(&format[*i + 1])) == -1)
			return (-1);
		*i = *i + a;
		return (sideint + colorint);
	}
	return (ft_get_color_id_other(format, i, a));
}

int			ft_get_color_id(const char *format, int *i)
{
	int a;
	int id;

	a = *i;
	while (ft_isdigit(format[a]))
		a++;
	if (format[a] == '}' && a != *i && (id = ft_atoi(&format[*i])) >= 0
			&& id <= 107)
	{
		*i = a;
		return (id);
	}
	else if (format[a] == '}')
		return (-1);
	a = 0;
	while (format[*i + a] != '}' && a < 5)
		a++;
	if ((*i == 5 && format[*i + a] != '}') || a == 0)
		return (-1);
	return (ft_get_color_id_macro(format, i, a));
}

t_printf	*ft_try_color(const char *format, int *i, int s)
{
	t_printf	*newb;
	t_printf	*newl;
	int			ibu;
	int			cid;

	ibu = *i - 1;
	if ((cid = ft_get_color_id(format, i)) != -1)
	{
		newl = ft_lstp_new(ft_strjoin_del(ft_strdup("\x1B["),
					ft_strjoin_del(ft_itoa(cid), ft_strdup("m"))), -1);
		*i = *i + 1;
	}
	else
		newl = ft_lstp_new(ft_strdup("{"), 1);
	newb = ft_lstp_new(ft_strsub(format, s, ibu - s), ibu - s);
	newb->next = newl;
	return (newb);
}
