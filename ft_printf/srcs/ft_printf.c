/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 18:21:00 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/02 06:31:04 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_expr_found(t_printf **p, t_printf *ret, int *totalen)
{
	(*p)->next = ret;
	(*p) = (*p)->next ? (*p)->next : *p;
	(*p) = (*p)->next ? (*p)->next : *p;
	if (ret->next->len == -1 && (*totalen = -1) == -1)
		return (1);
	return (0);
}

int			ft_verif_end(const char *format, t_printf **p, int s, int i)
{
	if (format[i - 1] != '%' && ((*p)->next = ft_lstp_new(
					ft_strsub(format, s, ft_strlen(&(format)[s])), -1)))
		return (1);
	return (0);
}

t_printf	*ft_data_init(int *totalen, int *i, int *s, t_printf **p)
{
	if (!((*p) = ft_memalloc(sizeof(t_printf))))
		return (NULL);
	*totalen = 0;
	*i = -1;
	*s = 0;
	return (*p);
}

void		ft_onemoreline(int *i, int *s)
{
	*s = *i;
	*i = *i - 1;
}

t_printf	*ft_mainprintf(const char *format, va_list arpt, int *totalen)
{
	int			i;
	int			s;
	t_printf	*p;
	t_printf	*begin;
	t_printf	*ret;

	if (!(begin = ft_data_init(totalen, &i, &s, &p)))
		return (NULL);
	while (format[++i])
	{
		if (format[i + 1] && ft_strindex("%{", format[i]) != -1 && (i = i + 1)
				>= 0 && ((format[i - 1] == '%' && (ret = ft_try_format(format,
								&i, s, arpt)))
			|| (format[i - 1] == '{' && (ret = ft_try_color(format, &i, s)))))
		{
			if (ft_expr_found(&p, ret, totalen))
				break ;
			ft_onemoreline(&i, &s);
		}
		if (!format[i])
			break ;
	}
	if (*totalen != -1 && ft_verif_end(format, &p, s, i))
		p = p->next;
	return (begin);
}
