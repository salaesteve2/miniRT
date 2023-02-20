/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 09:39:35 by sasalama          #+#    #+#             */
/*   Updated: 2022/02/07 09:39:22 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*x;
	unsigned char	a;

	i = 0;
	x = (unsigned char *)s;
	a = (unsigned char)c;
	while (i < n)
	{
		if (x[i] == a)
			return (&x[i]);
		i++;
	}
	return (0);
}
