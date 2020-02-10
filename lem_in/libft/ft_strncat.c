/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/09 17:48:16 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 22:54:17 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	int i;
	int a;

	a = -1;
	i = 0;
	while (dest[i] != '\0')
		i++;
	while (src[++a] != '\0' && a < (int)nb)
		dest[i + a] = src[a];
	dest[i + a] = '\0';
	return (dest);
}
