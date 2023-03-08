/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_range2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 08:59:25 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/08 15:42:47 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/geometry.h"

int	ft_process_range_sphere(double *nb)
{
	int	x;

	x = 4;
	while (x != 8)
	{
		if (nb[x] < 0 || nb[x] > 255)
			return (1);
		x++;
	}
	return (0);
}

int	ft_process_range_flat(double *nb)
{
	int	x;

	x = 3;
	while (x < 6)
	{
		if (nb[x] < -1 || nb[x] > 1)
			return (1);
		x++;
	}
	while (x != 10)
	{
		if (nb[x] < 0 || nb[x] > 255)
			return (1);
		x++;
	}
	if (nb[3] == 0 && nb[4] == 0 && nb[5] == 0)
		return (1);
	return (0);
}

int	ft_process_range_cylinder(double *nb)
{
	int	x;

	x = 3;
	while (x < 6)
	{
		if (nb[x] < -1 || nb[x] > 1)
			return (1);
		x++;
	}
	x += 2;
	while (x != 12)
	{
		if (nb[x] < 0 || nb[x] > 255)
			return (1);
		x++;
	}
	if (nb[3] == 0 && nb[4] == 0 && nb[5] == 0)
		return (1);
	return (0);
}
