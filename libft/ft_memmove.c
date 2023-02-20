/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:27:03 by sasalama          #+#    #+#             */
/*   Updated: 2022/02/03 10:19:41 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*a;
	const unsigned char	*b;

	a = dest;
	b = src;
	i = 0;
	if (dest == 0 && src == 0)
		return (0);
	if (a > b)
	{
		while (len--)
			a[len] = b[len];
	}
	else if (a < b)
	{
		while (i < len)
		{
			a[i] = b[i];
			i++;
		}
	}
	return (a);
}
