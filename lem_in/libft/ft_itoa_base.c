/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/17 00:05:51 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/30 04:55:28 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long long n, char *base)
{
	int		basenb;
	char	*ret;
	int		finalen;
	int		i;

	if (n == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	i = 0;
	basenb = ft_strlen(base);
	finalen = ft_nbrlen_base(n, basenb);
	if (!(ret = (char*)malloc(sizeof(char) * (finalen + 1))))
		return (NULL);
	if (n < 0 && (n = n * -1) > 0)
		ret[0] = '-';
	else if (n == 0)
		ret[0] = '0';
	ret[finalen] = '\0';
	while (n > 0 && (ret[finalen - (++i)] = base[n % basenb]))
		n = n / basenb;
	return (ret);
}
