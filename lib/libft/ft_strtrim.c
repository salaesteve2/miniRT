/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:15:48 by sasalama          #+#    #+#             */
/*   Updated: 2022/02/03 12:25:39 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	size_t	x[3];

	x[2] = 0;
	if (!s1)
		return (0);
	while (s1[x[2]] && is_char(s1[x[2]], set))
		x[2]++;
	x[1] = 0;
	while (s1[x[1]])
		x[1]++;
	while (x[1] > x[2] && is_char(s1[x[1] - 1], set))
		x[1]--;
	s = malloc((x[1] - x[2]) + 1);
	if (!s || !set)
		return (0);
	x[0] = 0;
	while (x[0] < x[1] - x[2])
	{
		s[x[0]] = (char)s1[x[0] + x[2]];
		x[0]++;
	}
	s[x[0]] = '\0';
	return (s);
}
