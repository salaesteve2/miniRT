/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:25:35 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/01 21:04:37 by sasalama         ###   ########.fr       */
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

int	ft_parallel_line(t_vector plane, t_vector line)
{
	double	res;

	res = ft_escalar_prod(plane, line);
	if (res == 0)
		return (0);
	return (1);
}

//necesito la ecuacion del plano
//para hallarlo
//vector normal ej: (1, -5, 3)
//punto: (0, 1, 0) 
//ax + by + cz + d = 0
//1x -5y +3z + d = 0
//1 * 0 -5 * 1 + 3 * 0 + d = 0
// d = 5
//ecuacion plano (1x -5y + 3z + 5 = 0)
//necesito la ecuacion de la recta
//para hallarlo
//necesito el vector y un punto
t_point ft_intersecction(t_vector plane, t_vector line)
{

}
