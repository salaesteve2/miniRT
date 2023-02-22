/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 09:49:51 by sasalama          #+#    #+#             */
/*   Updated: 2022/01/20 13:40:10 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*src;
	const unsigned char	*dest;

	i = 0;
	src = s1;
	dest = s2;
	while (i < n)
	{
		if (src[i] != dest[i])
			return (src[i] - dest[i]);
		i++;
	}
	return (0);
}
