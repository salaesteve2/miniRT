/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:26:01 by sasalama          #+#    #+#             */
/*   Updated: 2022/02/03 09:20:52 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_rev_char_tab(char *tab, int size, int sign)
{
	int		i;
	char	swap;

	i = 0;
	if (sign != 0)
		i++;
	while (i < size - 1)
	{
		swap = tab[i];
		tab[i] = tab[size - 1];
		tab[size - 1] = swap;
		i++;
		size--;
	}
}

static char	*ft_tab(char *s, int long sign, int n, int long number)
{
	if (!s)
		return (0);
	number = n;
	n = 0;
	if (number == 0)
		s[n++] = 0 + '0';
	if (sign != 0)
		s[n++] = '-';
	if (sign == 2)
		s[n++] = 8 + '0';
	while (number > 0)
	{
		s[n++] = number % 10 + '0';
		number = number / 10;
	}
	s[n] = '\0';
	ft_rev_char_tab(s, n, sign);
	return (s);
}

static int long	ft_digits(int long number, int long digits)
{
	while (number > 0)
	{
		digits++;
		number = number / 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char		*s;
	int long	sign;
	int long	number;
	int long	digits;

	sign = 0;
	digits = 1;
	if (n < 0)
	{
		sign = 1;
		if (n == -2147483648)
		{
			n = n / 10;
			sign = 2;
			digits++;
		}
		n = n * -1;
	}
	number = n;
	digits = ft_digits(number, digits);
	s = malloc(digits + 1);
	s = ft_tab(s, sign, n, number);
	return (s);
}
