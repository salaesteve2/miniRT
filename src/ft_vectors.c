/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:25:35 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/02 16:47:38 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/camera.h"
#include "../includes/color.h"
#include "../includes/file_reader.h"
#include "../includes/geometry.h"
#include "../includes/raytracer.h"
#include "../includes/vector.h"
#include "../includes/ft_process.h"
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
