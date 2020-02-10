/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 16:53:39 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 22:46:48 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *c_src;
	unsigned char *c_dst;

	c_src = (unsigned char*)src;
	c_dst = (unsigned char*)dst;
	if (c_dst == c_src)
		return (NULL);
	else if (c_src > c_dst)
		ft_memcpy(c_dst, src, len);
	else
	{
		c_dst += len - 1;
		c_src += len - 1;
		while (len--)
			*c_dst-- = *c_src--;
	}
	return (dst);
}
