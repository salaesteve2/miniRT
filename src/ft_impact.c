/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_impact.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:01:48 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/02 13:33:34 by valarcon         ###   ########.fr       */
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
	t_list *list;
	t_objet *obj;

	list = conf->my_scene.obj_lst;
	while (list != NULL)
	{
		obj = (t_objet *)conf->my_scene.obj_lst->content;
		if (obj->type == 1)
		{
			if (ft_vector_to_sphere(vision, (t_sphere *)obj->objet) == 1)
				return (1);
		}
		else if (obj->type == 2)
		{
			if (ft_vector_to_cylinder(vision, (t_cylinder *)obj->objet) == 1)
				return (1);
		}
		else if (obj->type == 3)
		{
			if (ft_vector_to_plane(vision, (t_m_plane *)obj->objet) == 1)
				return (1);
		}
		list = list->next;
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

t_point ft_coords_point_sphere(t_vector vision, t_sphere *objet)
{
    int distcent;

    int discenorig;

    int longray;

    int extra;

    int path;

    t_point result;

    distcent = (vision.x * objet->center.x + vision.y * objet->center.y + vision.z * objet->center.z) / sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);

    discenorig = sqrt(objet->center.x * objet->center.x + objet->center.y * objet->center.y + objet->center.z * objet->center.z);

    longray = sqrt(distcent * distcent + discenorig * discenorig);

    extra = sqrt(distcent * distcent + objet->radius * objet->radius);

    path = longray - extra;

    result.x = vision.x * path;
    result.y = vision.y * path;
    result.z = vision.z * path;

    return (result);
}
