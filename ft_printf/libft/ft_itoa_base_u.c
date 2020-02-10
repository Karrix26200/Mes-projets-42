/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base_u.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/20 02:14:24 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/22 02:02:42 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base_u(unsigned long long n, char *base)
{
	int		basenb;
	char	*ret;
	int		finalen;
	int		i;

	i = 0;
	basenb = ft_strlen(base);
	finalen = ft_nbrlen_base_u(n, basenb);
	if (!(ret = (char*)malloc(sizeof(char) * (finalen + 1))))
		return (NULL);
	if (n == 0)
		ret[0] = '0';
	ret[finalen] = '\0';
	while (n > 0 && (ret[finalen - (++i)] = base[n % basenb]))
		n = n / basenb;
	return (ret);
}
