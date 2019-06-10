/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 16:36:22 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 17:57:48 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp;
	t_list *newb;
	t_list *newstart;
	t_list *save;

	newstart = NULL;
	if (lst && f)
	{
		tmp = lst;
		save = f(tmp);
		newb = ft_lstnew(save->content, save->content_size);
		newstart = newb;
		tmp = tmp->next;
		while (tmp != NULL)
		{
			save = f(tmp);
			newb->next = ft_lstnew(save->content, save->content_size);
			tmp = tmp->next;
			newb = newb->next;
		}
	}
	return (newstart);
}
