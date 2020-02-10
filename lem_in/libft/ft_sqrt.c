/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sqrt.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/06 13:28:20 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 01:10:50 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int n)
{
	int	min;
	int	max;
	int	test;
	int	return_max;

	return_max = 1;
	min = 0;
	max = 46341;
	test = (max - min) / 2 + min;
	while (test * test != n)
	{
		if (test * test > n)
			max = test;
		if (test * test < n)
			min = test;
		if (max - min <= 1)
			return (return_max ? max : 0);
		test = (max - min) / 2 + min;
	}
	return (test);
}
