/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmapi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 18:32:18 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 23:05:31 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*newstr;

	newstr = NULL;
	if (s && f)
	{
		newstr = (char*)malloc(sizeof(*newstr) * ft_strlen(s) + 1);
		if (!newstr)
			return (NULL);
		i = -1;
		while (s[++i])
			newstr[i] = f(i, s[i]);
		newstr[i] = '\0';
	}
	return (newstr);
}
