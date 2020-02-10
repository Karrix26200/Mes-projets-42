/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstprintf.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 04:26:39 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/03 01:56:29 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_tostr_format(t_printf *ptfobject)
{
	int		i;
	int		a;
	char	*part;

	i = -1;
	a = 0;
	while (++i < ptfobject->len)
		a += ptfobject->str[i] != '\0';
	if (!(part = ft_strnew(a)))
		return (NULL);
	i = -1;
	a = -1;
	while (++i < ptfobject->len)
		if (ptfobject->str[i] != '\0')
			part[++a] = ptfobject->str[i];
	return (part);
}

void		ft_mod_controller(t_printf *begin, int mod, int fd, char **dst)
{
	if (mod == 0 && fd >= 0)
		write(fd, begin->str, begin->len);
	else if (mod == 1)
		*dst = ft_strjoin_del(*dst, ft_tostr_format(begin));
}

int			ft_lstp_controller(t_printf *begin, int mod, int fd, char **dst)
{
	t_printf	*before;
	int			totalen;
	int			error;

	totalen = 0;
	if (!begin || (error = 0))
		return (0);
	before = begin;
	begin = begin->next;
	ft_memdel((void**)&before);
	while (begin)
	{
		error = begin->len == -1 ? 1 : error;
		if (begin->str)
		{
			ft_mod_controller(begin, error ? -1 : mod, fd, dst);
			totalen += begin->len;
			ft_memdel((void**)&(begin->str));
		}
		before = begin;
		begin = begin->next;
		ft_memdel((void**)&before);
	}
	return (error ? -1 : totalen);
}

t_printf	*ft_lstp_new(char *str, int len)
{
	t_printf *tmp;

	if (!str || !(tmp = (t_printf*)ft_memalloc(sizeof(t_printf))))
	{
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&str);
		return (NULL);
	}
	tmp->str = str;
	tmp->len = len == -1 ? ft_strlen(str) : len;
	return (tmp);
}
