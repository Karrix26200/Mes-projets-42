/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_format_main.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 05:35:28 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/03 07:00:16 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_format_free(t_pformat *d)
{
	ft_memdel((void**)&d->flag);
	ft_memdel((void**)&d->size);
	ft_memdel((void**)&d);
}

int			ft_neg_format(t_printf *new, t_pformat *d)
{
	int number;

	number = 0;
	if (ft_strindex("dDixXoOuU", d->conv) != -1)
	{
		number = new->str[0] == '0' && new->len == 1 ? 0 : 1;
		number = new->str[0] == '-' ? -1 : number;
		if (number == -1)
		{
			new->str = ft_strrep(new->str, ft_strsub(new->str, 1,
						new->len - 1));
			new->len = new->len - 1;
		}
	}
	return (number);
}

t_printf	*ft_format_text(t_pformat *d, va_list arpt)
{
	t_printf	*new;
	int			neg;

	if (ft_strindex("sSpdDioOuUxXcCFfeEgG", d->conv) == -1)
		new = ft_lstp_new(ft_strinit(d->conv, 1), 1);
	else
		new = ft_lstp_new(ft_use_convert_fnc(arpt, ft_get_convert_fnc(
						ft_strindex("sSpdDioOuUxXcCFfeEgG", d->conv)), d), -1);
	if ((d->conv == 'S' || d->conv == 'C' || (d->conv == 'c' &&
					!(ft_strcmp(d->size, "l")))) && new->str[0] == -1)
	{
		new->str = ft_strrep(new->str, ft_strnew(0));
		new->len = -1;
		return (new);
	}
	new->len = (d->conv == 'c' && ft_strcmp(d->size, "l")) ||
		(d->conv == 'C' && new->len == 0) ? 1 : new->len;
	neg = ft_neg_format(new, d);
	ft_format_prec(new, d, neg);
	ft_format_flag(new, d, neg);
	if (d->conv == '\0')
		new->len = 0;
	return (new);
}

t_pformat	*ft_format_init(const char *format, int *i, va_list arpt)
{
	t_pformat *d;

	if (!(d = (t_pformat*)ft_memalloc(sizeof(t_pformat))))
		return (NULL);
	d->flag = ft_flag_save(format, i);
	d->width = ft_width_save(format, i, arpt, d);
	d->prec = ft_prec_save(format, i, arpt);
	d->size = ft_size_save(format, i);
	return (d);
}

t_printf	*ft_try_format(const char *format, int *i, int s, va_list arpt)
{
	t_printf	*newb;
	t_printf	*newl;
	t_pformat	*d;
	int			ibu;

	ibu = *i - 1;
	if (!(d = ft_format_init(format, i, arpt)))
		return (NULL);
	if ((d->conv = ft_conv_save(format, i)) || d->conv == '\0')
	{
		if (d->conv == 's' && !ft_strcmp(d->size, "l") && (d->conv = 'S'))
			d->size = ft_strrep(d->size, ft_strnew(0));
		else if (d->conv == 'U' && (d->conv = 'u'))
			d->size = ft_strrep(d->size, ft_strdup("ll"));
		newl = ft_format_text(d, arpt);
	}
	else
		newl = ft_lstp_new(ft_strsub(format, ibu, *i - ibu), *i - ibu);
	ft_format_free(d);
	if (newl->len != -1)
		newb = ft_lstp_new(ft_strsub(format, s, ibu - s), ibu - s);
	else
		newb = ft_lstp_new(ft_strdup(""), 0);
	newb->next = newl;
	return (newb);
}
