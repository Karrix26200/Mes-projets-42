/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_convert_fnc2.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/02 04:39:50 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/02 04:41:44 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_unicodenew(int c, int len)
{
	int		i;
	char	*tab;

	tab = ft_strnew(len + 1);
	i = 0;
	tab[0] = len == 1 ? (c >> 6) + 0xC0 : (c >> 12) | 0xE0;
	tab[0] = len == 3 ? (c >> 18) | 0xF0 : tab[0];
	while (len > 0)
		tab[len--] = ((c >> (i++) * 6) & 0x3F) | 0x80;
	return (tab);
}

char	*ft_convert_cm(va_list arpt, t_pformat *d)
{
	char	*tab;
	int		len;
	int		c;

	(void)d;
	c = (int)va_arg(arpt, int);
	len = (int)c > 0x7F && (int)c <= 0x7FF ? 1 : 0;
	len = (int)c > 0x7FF && (int)c <= 0xFFFF ? 2 : len;
	len = (int)c > 0xFFFF && (int)c <= 0x1FFFFF ? 3 : len;
	if (MB_CUR_MAX == 1 && c < 255)
		tab = ft_strinit(c, 1);
	else if (c < 0x11FFFF && c >= 0 && MB_CUR_MAX >= len + 1 &&
			!(c >= 0xD800 && c <= 0xDB7F) &&
			!(c >= 0xDC00 && c <= 0xDFFF))
		tab = len > 0 ? ft_unicodenew((int)c, len) : ft_strinit(c, 1);
	else
		tab = ft_strinit(-1, 1);
	return (tab);
}

char	*ft_convert_cms(int c, t_pformat *d)
{
	char	*tab;
	int		len;

	(void)d;
	len = (int)c > 0x7F && (int)c <= 0x7FF ? 1 : 0;
	len = (int)c > 0x7FF && (int)c <= 0xFFFF ? 2 : len;
	len = (int)c > 0xFFFF && (int)c <= 0x1FFFFF ? 3 : len;
	if (MB_CUR_MAX == 1 && c < 255)
		tab = ft_strinit(c, 1);
	else if (c < 0x11FFFF && c >= 0 && MB_CUR_MAX >= len + 1 &&
			!(c >= 0xD800 && c <= 0xDB7F) &&
			!(c >= 0xDC00 && c <= 0xDFFF))
		tab = len > 0 ? ft_unicodenew((int)c, len) : ft_strinit(c, 1);
	else
		tab = ft_strinit(-1, 1);
	return (tab);
}

char	*ft_free_c(char *finaltab, int option, char *c)
{
	if (option == 1)
		ft_memdel((void**)&c);
	return (finaltab);
}

char	*ft_convert_sm(va_list arpt, t_pformat *d)
{
	wchar_t *s;
	char	*c;
	char	*finaltab;
	int		i;
	int		len;

	len = 0;
	finaltab = ft_strnew(0);
	i = -1;
	s = va_arg(arpt, wchar_t*);
	if (s == NULL)
		return (ft_free_c(ft_strdup("(null)"), 1, finaltab));
	while (s[++i])
	{
		c = ft_convert_cms(s[i], d);
		len += ft_strlen(c);
		if (d->prec == len && d->prec != -1)
			return (ft_free_c(ft_strjoin_del(finaltab, c), 0, NULL));
		else if (d->prec < len && d->prec != -1)
			return (ft_free_c(finaltab, 1, c));
		else if (c[0] == -1)
			return (ft_free_c(ft_strrep(finaltab, ft_strinit(-1, 1)), 1, c));
		finaltab = ft_strjoin_del(finaltab, c);
	}
	return (finaltab);
}
