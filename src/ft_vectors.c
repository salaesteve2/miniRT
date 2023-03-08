/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:25:35 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/08 15:29:50 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/geometry.h"
#include "../lib/libft/libft.h"

//vector direccion plano y recta
t_vector	ft_coords_point_plane(t_m_plane *plane, t_vector line)
{
	double		nb;
	double		res;
	t_vector	point;

	nb = -(plane->point.x * plane->normal.x) - (plane->point.y * plane->normal.y) - (plane->point.z * plane->normal.z);
	res = -nb / ((line.x * plane->normal.x) + (line.y * plane->normal.y) + (line.z * plane->normal.z));
	point.x = res * line.x;
	point.y = res * line.y;
	point.z = res * line.z;
	return (point);
}
