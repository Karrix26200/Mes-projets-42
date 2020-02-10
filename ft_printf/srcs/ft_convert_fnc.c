/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_convert_fnc.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 01:41:18 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/02 04:43:07 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert_s(va_list arpt, t_pformat *d)
{
	char *test;

	test = ft_get_cast_other(d, arpt);
	return (test == NULL ? ft_strdup("(null)") : ft_strdup(test));
}

char	*ft_convert_p(va_list arpt, t_pformat *d)
{
	d->size = ft_strjoin_del(d->size, ft_strdup("ll"));
	return (ft_itoa_base(ft_get_cast_int(d, arpt), "0123456789abcdef"));
}

char	*ft_convert_d(va_list arpt, t_pformat *d)
{
	return (ft_itoa_base(ft_get_cast_int(d, arpt), "0123456789"));
}

char	*ft_convert_dm(va_list arpt, t_pformat *d)
{
	d->size = ft_strjoin_del(d->size, ft_strdup("l"));
	return (ft_itoa_base(ft_get_cast_int(d, arpt), "0123456789"));
}

char	*ft_convert_o(va_list arpt, t_pformat *d)
{
	char *str;

	str = ft_itoa_base_u(ft_get_cast_base(d, arpt), "01234567");
	return (str);
}
