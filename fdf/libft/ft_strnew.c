/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 17:59:30 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 19:08:26 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	int		i;

	i = -1;
	str = (char*)malloc(sizeof(*str) * (size + 1));
	if (!str)
		return (str);
	while (++i < (int)size)
		str[i] = '\0';
	str[i] = '\0';
	return (str);
}
