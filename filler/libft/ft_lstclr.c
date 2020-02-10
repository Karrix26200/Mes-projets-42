/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstclr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/11 19:44:28 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 16:42:58 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstclr(t_list *list, t_list *target, t_list *begin)
{
	t_list *tmp;

	if (target == list)
	{
		tmp = (list)->next;
		free(list);
		list = NULL;
		return (tmp);
	}
	else
		while (list)
		{
			if (list == target)
			{
				tmp->next = (list)->next;
				free(list);
				list = NULL;
				break ;
			}
			tmp = list;
			list = (list)->next;
		}
	return (begin);
}
