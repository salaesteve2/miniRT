/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_impact.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:01:48 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/02 17:59:41 by sasalama         ###   ########.fr       */
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

t_vector	ft_coords_point_cylinder(t_cylinder *obj, t_vector vision)
{
	(void)obj;
	return (vision);
}

int	ft_impact(t_conf *conf, t_vector vision)
{
	////calcular si HAY interseccion entre el vector con origen 0,0,0 y algun objeto de la lista
	t_list *list;
	t_objet *obj;

	list = conf->my_scene.obj_lst;
	while (list->content)
	{
		obj = (t_objet *)list->content;
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

t_objet	*ft_closet(t_conf *conf, t_vector vision)
{
	//calcular la distancia a los objetos con intersección, discernir el mas cercano y rellenar las coordenadas del punto de impacto a la vez que retorna el t_objet del objeto
	t_list		*list;
	t_objet		*obj;
	t_vector	coord;
	t_objet		*res;
	t_sphere	*tmp;
	t_m_plane	*tmp2;
	t_cylinder	*tmp3;
	double		mod;
	double		mod2;

	mod = 0;
	mod2 = 10000;
	list = conf->my_scene.obj_lst;
	obj = (t_objet *)list->content;
	res = obj;
	while (list->content)
	{
		obj = (t_objet *)list->content;
		if (obj->type == 1)
		{
			if (ft_vector_to_sphere(vision, (t_sphere *)obj->objet) == 1)
			{
				coord = ft_coords_point_sphere(vision, (t_sphere *)obj->objet);
				tmp = (t_sphere *)obj->objet;
				tmp->intersection = coord;
				mod = ft_module(coord);
				if (mod < mod2)
				{
					mod2 = mod;
					res = obj;
				}
			}
		}
		else if (obj->type == 2)
		{
			if (ft_vector_to_cylinder(vision, (t_cylinder *)obj->objet) == 1)
			{
				coord = ft_coords_point_cylinder((t_cylinder *)obj->objet, vision);
				tmp3 = (t_cylinder *)obj->objet;
				tmp3->intersection = coord;
				mod = ft_module(coord);
				if (mod < mod2)
				{
					mod2 = mod;
					res = obj;
				}
			}
		}
		else if (obj->type == 3)
		{
			if (ft_vector_to_plane(vision, (t_m_plane *)obj->objet) == 1)
			{
				coord = ft_coords_point_plane((t_m_plane *)obj->objet, vision);
				tmp2 = (t_m_plane *)obj->objet;
				tmp2->intersection = coord;
				mod = ft_module(coord);
				if (mod < mod2)
				{
					mod2 = mod;
					res = obj;
				}
			}
		}
		list = list->next;
	}
	return (res);
}

t_vector	ft_coords_point_sphere(t_vector vision, t_sphere *objet)
{
	int			distcent;
	int			discenorig;
	int			longray;
	int			extra;
	int			path;
	t_vector	result;

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
