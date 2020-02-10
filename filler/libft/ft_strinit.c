/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strinit.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 00:29:47 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 00:30:26 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinit(int c, int len)
{
	char	*str;

	if (!(str = ft_strnew(len)))
		return (str);
	while (len-- > 0)
		str[len] = c;
	return (str);
}
