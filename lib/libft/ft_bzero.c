/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:46:53 by sasalama          #+#    #+#             */
/*   Updated: 2022/01/20 13:14:59 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			len;
	unsigned char	*a;

	len = 0;
	a = s;
	while (len < n)
	{
		a[len] = 0;
		len++;
	}
}
