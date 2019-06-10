/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 18:39:11 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 23:12:06 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char *tmp;

	if (s)
	{
		tmp = NULL;
		if (!(tmp = (char*)malloc(sizeof(*tmp) * (len + 1))))
			return (NULL);
		tmp = ft_strncpy(tmp, &(s[start]), len);
		tmp[len] = '\0';
		return (tmp);
	}
	return (NULL);
}
