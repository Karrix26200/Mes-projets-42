/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_main.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/02 06:28:40 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/03 04:33:20 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list		arpt;
	int			totalen;
	t_printf	*begin;

	va_start(arpt, format);
	begin = ft_mainprintf(format, arpt, &totalen);
	totalen = ft_lstp_controller(begin, 0, 1, NULL);
	va_end(arpt);
	return (totalen);
}

int		ft_fprintf(int fd, const char *format, ...)
{
	va_list		arpt;
	int			totalen;
	t_printf	*begin;

	va_start(arpt, format);
	begin = ft_mainprintf(format, arpt, &totalen);
	totalen = ft_lstp_controller(begin, 0, fd, NULL);
	va_end(arpt);
	return (totalen);
}

int		ft_sprintf(char **dst, const char *format, ...)
{
	va_list		arpt;
	int			totalen;
	t_printf	*begin;

	ft_memdel((void**)dst);
	va_start(arpt, format);
	begin = ft_mainprintf(format, arpt, &totalen);
	totalen = ft_lstp_controller(begin, 1, -1, dst);
	va_end(arpt);
	return (totalen);
}

char	*ft_cprintf(const char *format, ...)
{
	va_list		arpt;
	int			totalen;
	t_printf	*begin;
	char		*dst;

	dst = NULL;
	va_start(arpt, format);
	begin = ft_mainprintf(format, arpt, &totalen);
	totalen = ft_lstp_controller(begin, 1, -1, &dst);
	va_end(arpt);
	return (dst);
}
