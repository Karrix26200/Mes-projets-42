/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrchr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 15:51:30 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 23:02:52 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	ptr = NULL;
	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			ptr = &((char*)s)[i];
	if ((char)c == s[i])
		return (&((char*)s)[i]);
	else if (ptr != NULL)
		return (ptr);
	else
		return (NULL);
}
