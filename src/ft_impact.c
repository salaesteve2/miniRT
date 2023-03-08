/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_impact.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:01:48 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/08 16:15:44 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/geometry.h"


t_vector	ft_coords_point_plane2(t_circle *plane, t_vector line)
{
	double		nb;
	double		res;
	t_vector	point;

	nb = -(plane->center.x * plane->normal.x) - (plane->center.y * plane->normal.y) - (plane->center.z * plane->normal.z);
	res = -nb / ((line.x * plane->normal.x) + (line.y * plane->normal.y) + (line.z * plane->normal.z));
	point.x = res * line.x;
	point.y = res * line.y;
	point.z = res * line.z;
	return (point);
}

t_vector	ft_coords_point_cylinder(t_cylinder *obj, t_vector vision)
{
	t_vector	norm;
	t_vector	aux;
	double		dist;
	t_vector	midpoint;
	t_vector	two_points;
	t_vector	normalplane;
	t_vector	pointplane;
	int			extra;
	double      angle;
    double      modvis;
    double		modaux;
	double		k;
	double		distaux;
	double	hipotenusa;
	t_vector	result;

	norm = normalize(provec(obj->dir, vision));
	two_points = vec(obj->center.x, obj->center.y, obj->center.z);
	dist = dot_prod(two_points, norm);
	if (dist > obj->radius)
		return (vec(0, 0, 0));
	extra = obj->dir.x * obj->center.x + obj->dir.y * obj->center.y + obj->dir.z * obj->center.z;
	aux = vec(obj->dir.x + norm.x * dist, obj->dir.y + norm.y * dist, obj->dir.z + norm.z * dist);
	normalplane = provec(norm, aux);
	pointplane.x = obj->center.x;
	pointplane.y = obj->center.y;
	pointplane.z = obj->center.z;
	k = (normalplane.x * pointplane.x + normalplane.y * pointplane.y + normalplane.z * pointplane.z) / (normalplane.x * vision.x + normalplane.y * vision.y + normalplane.z * vision.z);
	midpoint.x = k * vision.x;
	midpoint.y = k * vision.y;
	midpoint.z = k * vision.z;
	distaux = sqrt(obj->radius * obj->radius - dist * dist);
	modvis = sqrt(pow(vision.x, 2) + pow(vision.y, 2) + pow(vision.z, 2));
	modaux = sqrt(pow(obj->base.normal.x, 2) + pow(obj->base.normal.y, 2) + pow(obj->base.normal.z, 2));
	angle = acos((obj->base.normal.x * vision.x + obj->base.normal.y * vision.y + obj->base.normal.z * vision.z) / (modvis * modaux));
	angle = atan(dist / obj->radius);
	hipotenusa = distaux / sin(angle);
	if (vision.x + vision.y + vision.z > 0)
	{
		result.x = midpoint.x - vision.x * hipotenusa;
		result.y = midpoint.y - vision.y * hipotenusa;
		result.z = midpoint.z - vision.z * hipotenusa;
	}
	else
	{
		result.x = midpoint.x + vision.x * hipotenusa;
		result.y = midpoint.y + vision.y * hipotenusa;
		result.z = midpoint.z + vision.z * hipotenusa;
	}
	return (result);
}

int	ft_impact(t_conf *conf, t_vector vision)
{
	t_list	*list;
	t_objet	*obj;

	list = conf->my_scene.obj_lst;
	while (list->content)
	{
		obj = (t_objet *)list->content;
		if (obj->type == 1)
		{
			if (ft_vector_to_sphere(vision, (t_sphere *)obj->objet) == 1)
			{
				return (1);
			}
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
				printf("Ccoords:%f, %f, %f\n", coord.x, coord.y, coord.z);
				if (mod < mod2)
				{

					printf("coords:%f, %f, %f\n", coord.x, coord.y, coord.z);

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

	distcent = (vision.x * objet->center.x + vision.y * objet->center.y + vision.z * objet->center.z) / sqrt(pow(vision.x, 2) + pow(vision.y, 2) + pow(vision.z, 2));
	discenorig = sqrt(pow(objet->center.x, 2) + pow(objet->center.y, 2) + pow(objet->center.z, 2));
	longray = sqrt(distcent * distcent + discenorig * discenorig);
	extra = sqrt(distcent * distcent + objet->radius * objet->radius);
	path = longray - extra;
	result.x = vision.x * path;
	result.y = vision.y * path;
	result.z = vision.z * path;
	return (result);
}
