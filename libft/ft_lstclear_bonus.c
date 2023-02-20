/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:41:11 by salustianos       #+#    #+#             */
/*   Updated: 2022/02/01 09:48:06 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*s;
	int		i;

	i = 0;
	if (lst)
	{
		while (lst[i])
		{
			s = lst[i]-> next;
			ft_lstdelone(*lst, del);
			lst[i] = s;
		}
	}
}
