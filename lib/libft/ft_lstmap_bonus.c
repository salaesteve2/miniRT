/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:49:19 by salustianos       #+#    #+#             */
/*   Updated: 2022/02/01 09:42:17 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*s1;
	t_list	*s2;

	if (lst == NULL || f == NULL)
		return (NULL);
	s2 = 0;
	while (lst)
	{
		s1 = ft_lstnew((*f)(lst -> content));
		if (!s1)
		{
			ft_lstclear(&s2, del);
			return (NULL);
		}
		ft_lstadd_back(&s2, s1);
		lst = lst -> next;
	}
	return (s2);
}
