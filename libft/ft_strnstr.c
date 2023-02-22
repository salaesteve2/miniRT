/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 09:57:39 by sasalama          #+#    #+#             */
/*   Updated: 2022/02/07 09:52:38 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	x;
	size_t	z;
	char	*s;

	s = (char *)haystack;
	x = 0;
	if (*needle == 0 || haystack == needle)
		return (s);
	while (s[x] && x < len)
	{
		z = 0;
		while (s[x + z] && needle[z] && s[x + z] == needle[z] && x + z < len)
			z++;
		if (!needle[z])
			return (s + x);
		x++;
	}
	return (0);
}
