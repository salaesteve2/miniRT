/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:05:48 by sasalama          #+#    #+#             */
/*   Updated: 2022/02/03 10:27:10 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	len;

	len = 0;
	while (src[len])
		len++;
	if (dstsize == 0)
		return (len);
	len = 0;
	while (*(src + len) && len + 1 < dstsize)
	{
		dest[len] = src[len];
		len++;
	}
	dest[len] = '\0';
	len = 0;
	while (src[len] != '\0')
		len++;
	return (len);
}
