/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salustianosalamanca <salustianosalamanc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 09:41:49 by sasalama          #+#    #+#             */
/*   Updated: 2022/02/04 17:07:05 by salustianos      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	x;
	size_t	y;
	char	*s1;

	x = 0;
	y = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		return (ft_calloc(1, sizeof(char)));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	s1 = malloc(len + 1);
	if (!s1)
		return (0);
	while (s[x])
	{
		if (x >= start && y < len)
			s1[y++] = s[x];
		x++;
	}
	s1[y] = '\0';
	return (s1);
}
