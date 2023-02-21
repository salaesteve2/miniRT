/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_range.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:18:57 by sasalama          #+#    #+#             */
/*   Updated: 2023/02/21 09:03:32 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//Sugerencia: terminar todos los string en -2 para poder procesar los 0

int	ft_process_range_ambient_light(double *nb)
{
	int	x;

	x = 0;
	while (nb[x] != -2)
		x++;
	if (x > 4)
		return (1);
	if (nb[0] < 0 || nb[0] > 1.0)
		return (1);
	x = 1;
	while (nb[x] != -2)
	{
		if (nb[x] < 0 || nb[x] > 255)
			return (1);
		x++;
	}
	return (0);
}

//Coordenadas x,y,z no especifica rango

int	ft_process_range_camara(double *nb)
{
	int	x;

	x = 0;
	while (nb[x] != -2)
		x++;
	if (x > 7)
		return (1);
	x = 4;
	while (x < 6)
	{
		if (nb[x] < -1 || nb[x] > 1)
			return (1);
		x++;
	}
	if (nb[6] < 0 || nb[6] > 180)
		return (1);
	return (0);
}

int	ft_process_range_light(double *nb)
{
	int	x;

	x = 0;
	while (nb[x] != -2)
		x++;
	if (x > 7)
		return (1);
	x = 4;
	if (nb[x] < 0 || nb[x] > 1)
		return (1);
	return (0);
}
