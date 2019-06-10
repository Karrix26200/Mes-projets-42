/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_modifier_main.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 01:48:48 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/02 06:34:48 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

long long	ft_get_cast_int(t_pformat *d, va_list arpt)
{
	if (!ft_strcmp(d->size, "hh"))
		return ((signed char)va_arg(arpt, long long));
	else if (!ft_strcmp(d->size, "h"))
		return ((short)va_arg(arpt, long long));
	else if (!ft_strcmp(d->size, "l"))
		return ((long)va_arg(arpt, long long));
	else if (!ft_strcmp(d->size, "ll"))
		return ((long long)va_arg(arpt, long long));
	else if (!ft_strcmp(d->size, "j"))
		return ((intmax_t)va_arg(arpt, long long));
	else if (!ft_strcmp(d->size, "z"))
		return ((long long)va_arg(arpt, long long));
	return ((int)va_arg(arpt, long long));
}

long long	ft_get_cast_base(t_pformat *d, va_list arpt)
{
	if (!ft_strcmp(d->size, "hh"))
		return ((unsigned char)va_arg(arpt, long long));
	else if (!ft_strcmp(d->size, "h"))
		return ((unsigned short)va_arg(arpt, long long));
	else if (!ft_strcmp(d->size, "l"))
		return ((unsigned long)va_arg(arpt, long long));
	else if (!ft_strcmp(d->size, "ll"))
		return ((unsigned long long)va_arg(arpt, long long));
	else if (!ft_strcmp(d->size, "j"))
		return ((uintmax_t)va_arg(arpt, long long));
	else if (!ft_strcmp(d->size, "z"))
		return ((size_t)va_arg(arpt, long long));
	return ((unsigned)va_arg(arpt, long long));
}

void		*ft_get_cast_other(t_pformat *d, va_list arpt)
{
	if (!ft_strcmp(d->size, "hh"))
		return ((signed char *)va_arg(arpt, long long *));
	else if (!ft_strcmp(d->size, "h"))
		return ((short *)va_arg(arpt, long long *));
	else if (!ft_strcmp(d->size, "l"))
		return ((long *)va_arg(arpt, long long *));
	else if (!ft_strcmp(d->size, "ll"))
		return ((long long *)va_arg(arpt, long long *));
	else if (!ft_strcmp(d->size, "j"))
		return ((intmax_t *)va_arg(arpt, long long *));
	return ((char *)va_arg(arpt, long long *));
}
