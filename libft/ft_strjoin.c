/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:04:43 by sasalama          #+#    #+#             */
/*   Updated: 2022/02/03 12:26:09 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		x;
	int		y;
	int		z;
	char	*s;

	if (!s1)
		return (0);
	x = ft_strlen(s1);
	y = ft_strlen(s2);
	s = malloc(x + y + 1);
	if (!s)
		return (0);
	z = 0;
	while (s1[z])
	{
		s[z] = (char)s1[z];
		z++;
	}
	y = 0;
	while (s2[y])
		s[x++] = (char)s2[y++];
	s[x] = '\0';
	return (s);
}
