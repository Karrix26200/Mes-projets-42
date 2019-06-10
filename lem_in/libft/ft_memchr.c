/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 17:04:17 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 22:45:39 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char *ptr;

	ptr = (char*)s;
	while (n--)
	{
		if ((unsigned char)*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}
