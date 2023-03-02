/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_impact.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:01:48 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/02 09:52:16 by valarcon         ###   ########.fr       */
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

int	ft_impact(t_conf *conf, t_vector vision)
{
	////calcular si HAY interseccion entre el vector con origen 0,0,0 y algun objeto de la lista
	
	t_objet *obj = (t_objet *)conf->my_scene.obj_lst;

	while (obj != NULL)
	{
		if (obj->type == 1)
		{
			if (ft_vector_to_sphere(vision, obj->objet) == 1)
                return (1);
		}
		else if (obj->type == 2)
		{
			if (ft_vector_to_cylinder(vision, obj->objet) == 1)
				return (1);
		}
		else if (obj->type == 3)
		{
			if (ft_vector_to_plane(vision, obj->objet) == 1)
                return (1);
		}
		obj = obj->next;
	}


	return (0);
}

t_objet	*ft_closet(t_conf *conf, t_vector vision, t_point *point)
{
	//calcular la distancia a los objetos con intersección, discernir el mas cercano y rellenar las coordenadas del punto de impacto a la vez que retorna el t_objet del objeto
	(void)conf;
	(void)vision;
	(void)point;
	return (NULL);
}
