/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_convert_fnc1.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/02 04:37:12 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/02 04:39:18 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert_om(va_list arpt, t_pformat *d)
{
	char *str;

	d->size = ft_strjoin_del(d->size, ft_strdup("l"));
	str = ft_itoa_base_u(ft_get_cast_base(d, arpt), "01234567");
	return (str);
}

char	*ft_convert_u(va_list arpt, t_pformat *d)
{
	return (ft_itoa_base_u(ft_get_cast_base(d, arpt), "0123456789"));
}

char	*ft_convert_x(va_list arpt, t_pformat *d)
{
	char *str;

	str = ft_itoa_base_u(ft_get_cast_base(d, arpt), "0123456789abcdef");
	return (str);
}

char	*ft_convert_xm(va_list arpt, t_pformat *d)
{
	char *str;

	str = ft_itoa_base_u(ft_get_cast_base(d, arpt), "0123456789ABCDEF");
	return (str);
}

char	*ft_convert_c(va_list arpt, t_pformat *d)
{
	char	*str;

	if (ft_strcmp(d->size, "l"))
	{
		str = ft_strnew(1);
		str[0] = (char)va_arg(arpt, int);
		return (str);
	}
	return (ft_convert_cm(arpt, d));
}
