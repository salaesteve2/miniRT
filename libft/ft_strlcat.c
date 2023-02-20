/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salustianosalamanca <salustianosalamanc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:53:18 by sasalama          #+#    #+#             */
/*   Updated: 2022/02/02 13:08:07 by salustianos      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	y;
	size_t	z;

	z = ft_strlen(dst);
	y = 0;
	if (z >= dstsize)
		return (dstsize + ft_strlen(src));
	while (dstsize > 0 && z < dstsize - 1 && src[y])
		dst[z++] = src[y++];
	dst[z] = '\0';
	while (src[y++])
		z++;
	return (z);
}
