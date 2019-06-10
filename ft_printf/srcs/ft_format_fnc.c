/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_format_fnc.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/29 03:13:49 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/02 05:06:02 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_format_prec(t_printf *new, t_pformat *d, int neg)
{
	d->prec = ft_strindex("sSpdDioOuUxXcC", d->conv) == -1 ? -1 : d->prec;
	if (d->conv == 's' || d->conv == 'S')
		new->len = d->prec != -1 && d->prec < new->len ? d->prec : new->len;
	else if (d->conv != 'c' && d->conv != 'C')
	{
		if (d->prec == 0 && neg == 0 && !(new->len = 0))
		{
			new->str = ft_strrep(new->str, ft_strnew(0));
			new->len = 0;
		}
		if (d->prec > new->len)
		{
			new->str = ft_strjoin_del(ft_strinit('0', d->prec -
						new->len), new->str);
			new->len += d->prec - new->len;
		}
	}
}

void	ft_fflag_ab(t_printf *new, t_pformat *d, int frontchar)
{
	int i;

	if (frontchar != 'n' && ft_strindex(d->flag, '-') == -1 &&
			ft_strindex("dDi", d->conv) != -1)
	{
		i = 0;
		while (new->str[i] == ' ')
			i++;
		new->str[i == 0 ? 0 : i - 1] = frontchar;
	}
	else if (frontchar != 'n' && ft_strindex("dDi", d->conv) != -1)
	{
		ft_strdecale(&(new->str));
		new->str[0] = frontchar;
	}
}

void	ft_fflag_a(t_printf *new, t_pformat *d, int frontchar, int widthchar)
{
	if (ft_strindex(d->flag, '-') != -1)
		new->str = ft_strjoin_dell(new->str, ft_strinit(widthchar,
					d->width - new->len), new->len, d->width - new->len);
	else
	{
		new->str = ft_strjoin_del(ft_strinit(widthchar, d->width - new->len),
				new->str);
		if (ft_strindex("xXp", d->conv) != -1 && ft_strindex("xXp", new->str[
					d->width - new->len + 1]) != -1 && widthchar == '0')
		{
			new->str[d->width - new->len + 1] = '0';
			new->str[1] = d->conv == 'x' || d->conv == 'p' ? 'x' : 'X';
		}
	}
	new->len += d->width - new->len;
	ft_fflag_ab(new, d, frontchar);
}

void	ft_fflag_b(t_printf *new, t_pformat *d, int neg)
{
	if ((ft_strindex(d->flag, '#') != -1 && ft_strindex("oOxX", d->conv) != -1)
			|| d->conv == 'p')
	{
		if (((ft_strindex("xX", d->conv) != -1 && neg != 0)
		|| d->conv == 'p') && (new->len += 2))
			new->str = ft_strjoin_del(ft_strdup(d->conv == 'x' ||
						d->conv == 'p' ? "0x" : "0X"), new->str);
		else if ((d->conv == 'o' || d->conv == 'O') && new->str[0] != '0'
				&& (new->len += 1))
			new->str = ft_strjoin_del(ft_strdup("0"), new->str);
		else if (new->str[0] == '\0' && new->len == 0 && neg != 0
				&& (new->len += 1))
			new->str = ft_strrep(new->str, ft_strdup("0"));
	}
}

void	ft_format_flag(t_printf *new, t_pformat *d, int neg)
{
	char widthchar;
	char frontchar;

	ft_fflag_b(new, d, neg);
	frontchar = ft_strindex(d->flag, ' ') != -1 ? ' ' : 'n';
	frontchar = ft_strindex(d->flag, '+') != -1 ? '+' : frontchar;
	frontchar = neg == -1 ? '-' : frontchar;
	if (ft_strindex(d->flag, '0') != -1 && ft_strindex(d->flag, '-') == -1 &&
			(d->prec == -1 || ft_strindex("scSC", d->conv) != -1))
		widthchar = '0';
	else
		widthchar = ' ';
	if (d->width > new->len)
		ft_fflag_a(new, d, frontchar, widthchar);
	else
	{
		if (frontchar != 'n' && ft_strindex("dDi", d->conv) != -1)
		{
			new->str = ft_strjoin_del(ft_strinit(frontchar, 1), new->str);
			new->len++;
		}
	}
}
