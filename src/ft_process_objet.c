/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_objet.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:43:01 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/08 16:42:50 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/geometry.h"

double	dot_prod(t_vector u, t_vector v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

double	magnitude(t_vector u)
{
	return (sqrt(dot_prod(u, u)));
}

t_vector	prod(t_vector u, double lamda)
{
	return (vec(u.x * lamda, u.y * lamda, u.z * lamda));
}

t_vector	add(t_vector u, t_vector v)
{
	return (vec(u.x + v.x, u.y + v.y, u.z + v.z));
}

t_vector	provec(t_vector u, t_vector v)
{
	double	x;
	double	y;
	double	z;

	x = u.y * v.z - u.z * v.y;
	y = - (u.x * v.z - u.z * v.x);
	z = u.x * v.y - u.y * v.x;
	return (vec(x, y, z));
}
