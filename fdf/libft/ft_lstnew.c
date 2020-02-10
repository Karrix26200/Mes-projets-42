/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tdautrem <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 15:07:20 by tdautrem     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 19:00:43 by tdautrem    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *list;

	list = (t_list*)malloc(sizeof(*list));
	if (!list)
		return (NULL);
	if (content != NULL)
	{
		list->content = (void*)malloc(sizeof(content_size) + 1);
		if (!list->content)
			return (NULL);
		ft_memcpy(list->content, (void*)content, content_size);
	}
	else
		list->content = NULL;
	list->content_size = !content ? 0 : content_size;
	list->next = NULL;
	return (list);
}
