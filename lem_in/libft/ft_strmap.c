/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 18:23:31 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 23:04:26 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
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
			newstr[i] = f(s[i]);
		newstr[i] = '\0';
	}
	return (newstr);
}
