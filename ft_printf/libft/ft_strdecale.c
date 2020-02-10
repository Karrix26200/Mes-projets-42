/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdecale.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 06:27:12 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 06:27:44 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_strdecale(char **str)
{
	int	i;
	int	len;

	len = ft_strlen(*str);
	if (len < 2)
		return ;
	i = 0;
	while (len - (++i) - 1 >= 0)
		(*str)[len - i] = (*str)[len - i - 1];
}
