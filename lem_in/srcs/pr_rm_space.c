/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_rmsps.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tvarnier <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/13 03:29:25 by tvarnier     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 17:12:53 by tvarnier    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		ft_count_letters(char const *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	while (s[++i])
		if (s[i] != c)
			count++;
	return (count);
}

int		ft_count_words(char const *s, char c)
{
	int		i;
	int		nbr_words;
	int		verif;

	verif = 1;
	nbr_words = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] != c && verif == 1)
		{
			nbr_words++;
			verif = 0;
		}
		else if (s[i] == c && verif == 0)
			verif = 1;
	}
	return (nbr_words);
}

char	*ft_rm_space(char *s)
{
	char	*res;
	int		nbr_words;
	int		nbr_letters;
	int		i;
	int		a;

	res = NULL;
	nbr_letters = ft_count_letters(s, ' ');
	nbr_words = ft_count_words(s, ' ');
	if (!(res = ft_strnew(nbr_letters + (nbr_words - 1))))
		return (NULL);
	i = -1;
	a = 0;
	while (s[++i] && a < nbr_letters + (nbr_words - 1))
	{
		if (s[i] == ' ' && i != 0 && s[i - 1] != ' ')
			res[a++] = ' ';
		else if (s[i] != ' ')
			res[a++] = s[i];
	}
	return (res);
}
