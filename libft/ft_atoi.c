/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:13:54 by sasalama          #+#    #+#             */
/*   Updated: 2022/02/03 12:59:24 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi2(int long numberint, int x)
{
	if ((numberint > 2147483648 || numberint < -2147483648) && x == 1)
		return (0);
	else if ((numberint > 2147483648 || numberint < -2147483648) && x == 0)
		return (-1);
	if (x == 1)
		numberint = numberint * -1;
	return (numberint);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			x;
	int long	numberint;

	i = 0;
	x = 0;
	numberint = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\n')
		i++;
	if (str[i] == '-')
		x = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		else
			numberint = (str[i] - '0') + numberint * 10;
		i++;
	}
	return (ft_atoi2(numberint, x));
}
