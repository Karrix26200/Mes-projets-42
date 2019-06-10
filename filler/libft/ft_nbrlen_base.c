/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nbrlen_base.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/17 21:52:25 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/20 01:16:59 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbrlen_base(long long n, int base)
{
	int i;

	i = -1;
	if (n < 0 && !(i = 0))
		n = n * -1;
	i += n == 0;
	while (n > 0 && ++i >= 0)
		n = n / base;
	return (i + 1);
}
