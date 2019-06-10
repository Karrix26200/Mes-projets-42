/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcat.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/09 16:50:16 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 22:54:44 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int i;
	int a;

	a = -1;
	i = 0;
	while (dest[i] != '\0')
		i++;
	while (src[++a] != '\0')
		dest[i + a] = src[a];
	dest[i + a] = '\0';
	return (dest);
}
