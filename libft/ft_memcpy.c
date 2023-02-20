/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salustianosalamanca <salustianosalamanc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:38:11 by sasalama          #+#    #+#             */
/*   Updated: 2022/01/20 19:09:50 by salustianos      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *str, const void *str2, size_t n)
{
	size_t				i;
	unsigned char		*a;
	const unsigned char	*b;

	i = 0;
	a = str;
	b = str2;
	if (str == 0 && str2 == 0)
		return (0);
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (a);
}
