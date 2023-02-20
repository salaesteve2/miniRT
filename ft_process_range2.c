/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_range2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 08:59:25 by sasalama          #+#    #+#             */
/*   Updated: 2023/02/20 09:11:50 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_process_range_sphere(double *nb)
{
	int	x;

	x = 0;
	while (nb[x] != -2)
		x++;
	if (x > 7)
		return (1);
	x = 5;
	while (nb[x] != -2)
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

	x = 0;
	while (nb[x] != -2)
		x++;
	if (x > 9)
		return (1);
	x = 4;
	while (x < 7)
	{
		if (nb[x] < -1 || nb[x] > 1)
			return (1);
		x++;
	}
	while (nb[x] != -2)
	{
		if (nb[x] < 0 || nb[x] > 255)
			return (1);
		x++;
	}
	return (0);
}

int	ft_process_range_cylinder(double *nb)
{
	int	x;

	x = 0;
	while (nb[x] != -2)
		x++;
	if (x > 11)
		return (1);
	x = 4;
	while (x < 7)
	{
		if (nb[x] < -1 || nb[x] > 1)
			return (1);
		x++;
	}
	x += 2;
	while (nb[x] != -2)
	{
		if (nb[x] < 0 || nb[x] > 255)
			return (1);
		x++;
	}
	return (0);
}
