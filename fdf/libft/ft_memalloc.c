/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 17:47:08 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 14:10:59 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*ptr;
	char	*ptr2;

	ptr = (void*)malloc(sizeof(*ptr) * size);
	if (!ptr)
		return (NULL);
	ptr2 = ptr;
	while (size--)
		*ptr2++ = 0;
	return (ptr);
}
