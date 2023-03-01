/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_impact.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:01:48 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/01 09:30:04 by sasalama         ###   ########.fr       */
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

int	ft_impact(t_conf *conf, t_point *point)
{
	(void)conf;
	point->x = 0;
	point->y = 0;
	point->z = 0;
	return (0);
}

int	ft_closet(t_conf *conf, t_objet *obj)
{
	(void)conf;
	(void)obj;
	return (0);
}
