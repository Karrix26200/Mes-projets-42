/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 14:15:40 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 14:22:42 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int i;
	int j;

	j = 0;
	while (haystack[j] && j < (int)len)
	{
		i = 0;
		while (i + j < (int)len && haystack[i + j] == needle[i] && needle[i])
		{
			i++;
		}
		if (!needle[i])
		{
			return ((char*)haystack + j);
		}
		j++;
	}
	return (0);
}
