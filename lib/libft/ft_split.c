/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 09:49:37 by sasalama          #+#    #+#             */
/*   Updated: 2022/02/07 10:09:26 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s2, char c)
{
	int	x;
	int	y;
	int	z;

	x = 0;
	y = 0;
	z = 0;
	while (s2[x])
	{
		if (s2[x] != c && z == 0)
		{
			z = 1;
			y++;
		}
		else if (s2[x] == c)
			z = 0;
		x++;
	}
	return (y);
}

static char	*ft_word(char const *s3, int z, int x)
{
	int		i;
	char	*s4;

	i = 0;
	s4 = malloc(x - z + 1);
	if (!s4)
		return (0);
	while (z < x)
	{
		s4[i] = s3[z];
		i++;
		z++;
	}
	s4[i] = '\0';
	return (s4);
}

static char	**ft_clear(char **s1, size_t x)
{
	size_t	y;

	y = 0;
	while (y < x)
	{
		free(s1[y]);
		y++;
	}
	free (s1);
	return (0);
}

int	ft_table(int *x2)
{
	x2[0] = 0;
	x2[1] = 0;
	x2[2] = -1;
	return (x2[0]);
}

char	**ft_split(char const *s, char c)
{
	int		x[3];
	char	**s1;

	x[0] = ft_table(x);
	if (!s)
		return (0);
	s1 = malloc((ft_countwords(s, c) + 1) * sizeof(char *));
	if (!s1)
		return (0);
	while (x[0] <= (int)ft_strlen(s))
	{
		if (s[x[0]] != c && x[2] == -1)
			x[2] = x[0];
		else if ((s[x[0]] == c || x[0] == (int)ft_strlen(s)) && x[2] >= 0)
		{
			s1[x[1]] = ft_word(s, x[2], x[0]);
			if (!s1[x[1]])
				return (ft_clear(s1, x[1]));
			x[2] = -1;
			x[1]++;
		}
		x[0]++;
	}
	s1[x[1]] = 0;
	return (s1);
}
