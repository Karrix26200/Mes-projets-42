/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/09 11:38:18 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 22:56:04 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	int i;

	i = -1;
	while (++i < (int)n && src[i] != '\0')
		dest[i] = src[i];
	while (i < (int)n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
