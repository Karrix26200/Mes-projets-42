/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin_del.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 00:30:40 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/14 06:01:29 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_del(char *s1, char *s2)
{
	char	*newstr;

	if (!s1 && !s2)
		return (ft_strnew(0));
	else if (!s1)
	{
		newstr = ft_strdup(s2);
		ft_strdel(&s2);
	}
	else if (!s2)
	{
		newstr = ft_strdup(s1);
		ft_strdel(&s1);
	}
	else
	{
		newstr = ft_strjoin(s1, s2);
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	return (newstr);
}
