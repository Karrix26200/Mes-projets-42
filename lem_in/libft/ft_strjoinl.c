/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoinl.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 06:23:28 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 06:25:55 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinl(const char *s1, const char *s2, int l1, int l2)
{
	char	*newstr;
	int		i;
	int		j;

	newstr = NULL;
	if (s1 && s2)
	{
		newstr = (char*)malloc(sizeof(*newstr) * (l1 + l2 + 1));
		if (!newstr)
			return (NULL);
		i = -1;
		j = -1;
		while (++i < l1)
			newstr[++j] = s1[i];
		i = -1;
		while (++i < l2)
			newstr[++j] = s2[i];
		newstr[++j] = '\0';
	}
	return (newstr);
}
