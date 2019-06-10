/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 19:16:52 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/20 03:44:33 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*newstr;
	int		i;
	int		j;

	newstr = NULL;
	if (s1 && s2)
	{
		newstr = (char*)malloc(sizeof(*newstr) * (ft_strlen(s1) +
				ft_strlen(s2) + 1));
		if (!newstr)
			return (NULL);
		i = -1;
		j = -1;
		while (s1[++i])
			newstr[++j] = s1[i];
		i = -1;
		while (s2[++i])
			newstr[++j] = s2[i];
		newstr[++j] = '\0';
	}
	return (newstr);
}
