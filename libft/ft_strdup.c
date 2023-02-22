/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:34:38 by sasalama          #+#    #+#             */
/*   Updated: 2022/01/25 12:39:13 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		x;
	char	*s2;

	x = 0;
	while (s1[x] != '\0')
		x++;
	s2 = malloc(sizeof(char) * x + 1);
	if (s2 == 0)
		return (0);
	x = 0;
	while (*(s1 + x))
	{
		s2[x] = s1[x];
		x++;
	}
	s2[x] = '\0';
	return (s2);
}
