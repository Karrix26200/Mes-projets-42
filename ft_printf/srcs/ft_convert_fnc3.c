/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_convert_fnc3.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/02 04:41:12 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/03 05:50:54 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert_f(va_list arpt, t_pformat *d)
{
	return (ft_ftoa(va_arg(arpt, double), d->prec));
}

char	*ft_convert_e_motor(double realfloat, t_pformat *d)
{
	int i;
	int neg;

	i = 0;
	neg = 1;
	if (realfloat != 0)
	{
		if (realfloat < 0 && (neg = -1) == -1)
			realfloat *= -1;
		while (realfloat < 1)
		{
			realfloat *= 10;
			i--;
		}
		while (realfloat > 9)
		{
			realfloat /= 10;
			i++;
		}
	}
	return (ft_strjoin_del(ft_ftoa(realfloat * neg, d->prec),
				ft_cprintf("%c%+.2d", d->conv, i)));
}

char	*ft_convert_e(va_list arpt, t_pformat *d)
{
	double realfloat;

	realfloat = va_arg(arpt, double);
	return (ft_convert_e_motor(realfloat, d));
}

int		ft_exp_calc(double realfloat)
{
	int i;
	int neg;

	i = 0;
	if (realfloat < 0)
		realfloat *= -1;
	if (realfloat != 0)
	{
		if (realfloat < 0 && (neg = -1) == -1)
			realfloat *= -1;
		while (realfloat < 1)
		{
			realfloat *= 10;
			i--;
		}
		while (realfloat > 9)
		{
			realfloat /= 10;
			i++;
		}
	}
	return (i);
}

char	*ft_convert_g(va_list arpt, t_pformat *d)
{
	double	realfloat;
	int		exp;
	char	*final;
	int		i;

	d->conv = d->conv == 'g' ? 'e' : 'E';
	d->prec = d->prec == -1 ? 5 : d->prec - 1;
	realfloat = va_arg(arpt, double);
	exp = ft_exp_calc(realfloat);
	if (exp < -4 || exp >= d->prec + 1)
		final = ft_convert_e_motor(realfloat, d);
	else
		final = ft_ftoa(realfloat, d->prec);
	i = 0;
	while (final[i] != d->conv && final[i])
		i++;
	exp = i - 1;
	while (final[exp] == '0' && exp >= 0)
		exp--;
	if (final[exp] == '.' && exp >= 0)
		exp--;
	return (ft_strjoin_del(ft_strsub(final, 0, exp + 1), ft_strsub(final, i,
					ft_strlen(final) - i)));
}
