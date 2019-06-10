/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/08 11:03:57 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 22:56:13 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int boolwhile;
	int i;

	i = 0;
	boolwhile = 1;
	while (boolwhile)
	{
		dest[i] = src[i];
		boolwhile = src[i] == '\0' ? 0 : 1;
		i++;
	}
	return (dest);
}
