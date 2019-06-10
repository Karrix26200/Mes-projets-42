/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/11 10:12:21 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 22:56:41 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		length;
	char	*dest;

	length = 0;
	while (src[length])
		length++;
	dest = (char*)malloc(sizeof(*src) * length + 1);
	if (dest == NULL)
		return (dest);
	length = -1;
	while (src[++length])
		dest[length] = src[length];
	dest[length] = '\0';
	return (dest);
}
