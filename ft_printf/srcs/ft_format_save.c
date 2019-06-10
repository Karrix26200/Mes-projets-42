/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_format_save.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/28 01:49:51 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/03 06:42:51 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_flag_save(const char *format, int *i)
{
	int		len;
	char	*str;

	len = 0;
	while (ft_strindex("0+- #", format[*i + len]) != -1)
		len++;
	str = ft_strsub(format, *i, len);
	*i += len;
	return (str);
}

int		ft_width_save(const char *format, int *i, va_list arpt, t_pformat *d)
{
	int		len;
	char	*str;
	int		result;
	int		wildbool;

	len = -1;
	wildbool = 0;
	while (ft_isdigit(format[*i + (++len)]) || format[*i + len] == '*')
		wildbool = format[*i + len] == '*' ? 1 : wildbool;
	if (wildbool)
		result = va_arg(arpt, int);
	if (len > 0 && format[*i + len - 1] == '*')
	{
		str = ft_strnew(0);
		if (result < 0 && (result = result * -1) >= 0)
			d->flag = ft_strjoin_del(d->flag, ft_strdup("-"));
	}
	else
	{
		str = ft_strsub(format, wildbool ? *i + 1 : *i, len);
		result = len == 0 ? -1 : ft_atoi(str);
	}
	*i += len;
	ft_memdel((void**)&str);
	return (result);
}

int		ft_prec_save(const char *format, int *i, va_list arpt)
{
	int		len;
	char	*str;
	int		result;

	len = 0;
	if (!(format[*i] == '.' && (len = 1)))
		return (-1);
	while (ft_isdigit(format[*i + len]))
		len++;
	if (len == 1 && format[*i + len] != '*' && (*i)++)
		return (0);
	if (format[*i + len] == '*' && (len++))
		str = ft_itoa(va_arg(arpt, int));
	else
		str = ft_strsub(format, *i + 1, len - 1);
	*i += len;
	result = str[0] == '-' ? -1 : ft_atoi(str);
	ft_memdel((void**)&str);
	return (result);
}

char	*ft_size_save(const char *format, int *i)
{
	if (format[*i] == format[*i + 1] && ft_strindex("hl", format[*i]) != -1)
		return (ft_strsub(format, (*i += 2) - 2, 2));
	else if (ft_strindex("hljz", format[*i]) != -1)
		return (ft_strsub(format, (*i += 1) - 1, 1));
	return (ft_strnew(0));
}

char	ft_conv_save(const char *format, int *i)
{
	if (format[*i] != '\0')
		return (format[(*i)++]);
	return (format[*i]);
}
