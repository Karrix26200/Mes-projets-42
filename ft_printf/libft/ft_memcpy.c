/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 16:14:35 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 22:42:48 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *ptr;
	char *ptr2;

	ptr2 = (void*)src;
	ptr = dst;
	while (n-- > 0)
		*ptr++ = *ptr2++;
	return (dst);
}
