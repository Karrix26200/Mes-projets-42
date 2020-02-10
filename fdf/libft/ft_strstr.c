/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/09 12:14:15 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 19:29:27 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	j = 0;
	if (!needle[0])
		return ((char*)&haystack[0]);
	while (haystack[j])
	{
		i = 0;
		while (haystack[i + j] == needle[i] && needle[i])
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
