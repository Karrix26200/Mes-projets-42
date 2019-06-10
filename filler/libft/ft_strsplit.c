/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 21:27:45 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 23:15:46 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void		ft_next_1(char *s, int *i, char c)
{
	while (s[*i] && s[*i] == c)
		*i = *i + 1;
}

static void		ft_next_2(char **str, int *mots, int j)
{
	str[*mots][j] = '\0';
	*mots = *mots + 1;
}

static int		ft_next_3(char *s, int i, char c)
{
	int j;

	j = 0;
	while (s[i + j] && s[i + j] != c)
		j++;
	return (j);
}

static void		ft_next(char **str, char *s, char c)
{
	int mots;
	int i;
	int j;

	mots = 0;
	i = 0;
	while (s[i])
	{
		ft_next_1(s, &i, c);
		if (s[i])
		{
			j = ft_next_3(s, i, c);
			str[mots] = (char*)malloc(sizeof(str) * j + 1);
			if (!str[mots])
				return ;
			j = 0;
			while (s[i + j] && s[i + j] != c)
			{
				str[mots][j] = s[i + j];
				j++;
			}
			ft_next_2(str, &mots, j);
			i += j;
		}
	}
}

char			**ft_strsplit(const char *s, char c)
{
	int		i;
	int		mots;
	char	**str;

	if (!s || !c)
		return (NULL);
	mots = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			mots++;
		while (s[i] && s[i] != c)
			i++;
	}
	str = (char**)malloc(sizeof(str) * mots + 1);
	if (!str)
		return (NULL);
	str[mots] = 0;
	ft_next(str, (char*)s, c);
	return (str);
}
