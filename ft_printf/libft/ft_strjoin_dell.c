/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin_dell.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 06:26:12 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 06:27:01 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_dell(char *s1, char *s2, int l1, int l2)
{
	char *newstr;

	newstr = ft_strjoinl(s1, s2, l1, l2);
	ft_memdel((void**)&s1);
	ft_memdel((void**)&s2);
	return (newstr);
}
