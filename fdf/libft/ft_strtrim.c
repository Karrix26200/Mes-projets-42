/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 19:39:11 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 23:14:40 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	int		startlen;
	int		endlen;
	int		strlen;
	char	*newstr;
	int		i;

	if (!s)
		return (NULL);
	i = -1;
	startlen = 0;
	strlen = ft_strlen(s);
	endlen = strlen - 1;
	while (s[startlen] == ' ' || s[startlen] == '\n' || s[startlen] == '\t')
		startlen++;
	if (startlen == endlen + 1)
		return (ft_strnew(0));
	while (s[endlen] == ' ' || s[endlen] == '\n' || s[endlen] == '\t')
		endlen--;
	newstr = (char*)malloc(sizeof(*newstr) * (endlen - startlen + 1) + 1);
	if (!newstr)
		return (newstr);
	while (startlen < endlen + 1)
		newstr[++i] = s[startlen++];
	newstr[++i] = '\0';
	return (newstr);
}
