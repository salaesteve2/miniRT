/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:45:00 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/14 10:33:49 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/geometry.h"

double	ft_escalar_prod(t_vector a, t_vector b)
{
	double	res;

	res = a.x * b.x + a.y * b.y + a.z + b.z;
	return (res);
}

double	ft_module(t_vector v)
{
	double	res;

	res = v.x * v.x + v.y * v.y + v.z * v.z;
	res = sqrt(res);
	return (res);
}

int	ft_dist_point_plane(t_vector plane, int extra, t_vector point)
{
	int	res;

	res = ((plane.x * point.x + plane.y * point.y + plane.z * point.z + extra) / sqrt(pow(plane.x, 2) + pow(plane.y, 2) + pow(plane.z, 2)));
	if (res < 0)
		res *= -1;
	return (res);
}

int	rgb_to_int(const t_rgb rgb)
{
	return (rgb.red << 16 | rgb.green << 8 | rgb.blue);
}

int	ft_coords_light_sphere(t_sphere *sphere, t_vector light)
{
	t_vector	aux;
	t_vector	aux2;

	aux.o.x = light.x;
	aux.o.y = light.y;
	aux.o.z = light.z;
	aux.x = sphere->intersection.x - light.x;
	aux.y = sphere->intersection.y - light.y;
	aux.z = sphere->intersection.z - light.z;
	aux2 = ft_coords_point_sphere(aux, sphere);
	if (sphere->intersection.x == aux2.x && sphere->intersection.y == aux2.y && sphere->intersection.y == aux2.y)
		return (1);
	return (0);
}

int	ft_coords_light_cylinder(t_cylinder *cylinder, t_vector light)
{
	t_vector	aux;
	t_vector	aux2;

	aux.o.x = light.x;
	aux.o.y = light.y;
	aux.o.z = light.z;
	aux.x = cylinder->intersection.x - light.x;
	aux.y = cylinder->intersection.y - light.y;
	aux.z = cylinder->intersection.z - light.z;
	aux2 = ft_coords_point_cylinder(cylinder, aux);
	if (cylinder->intersection.x == aux2.x && cylinder->intersection.y == aux2.y && cylinder->intersection.y == aux2.y)
		return (1);
	return (0);
}

int	ft_coords_light_plane(t_m_plane *plane, t_vector light)
{
	t_vector	aux;
	t_vector	aux2;

	aux.o.x = light.x;
	aux.o.y = light.y;
	aux.o.z = light.z;
	aux.x = plane->intersection.x - light.x;
	aux.y = plane->intersection.y - light.y;
	aux.z = plane->intersection.z - light.z;
	aux2 = ft_coords_point_plane(plane, aux);
	if (plane->intersection.x == aux2.x && plane->intersection.y == aux2.y && plane->intersection.y == aux2.y)
		return (1);
	return (0);
}

int	ft_light_intersec(t_objet *obj, t_conf *conf)
{
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_m_plane	*plane;
	t_sphere	*sphere2;
	t_cylinder	*cylinder2;
	t_m_plane	*plane2;
	t_objet		*obj2;
	int			coords_light;
	t_list		*list;
	double		mod;
	double		mod2;
	t_objet		*res;

	mod = 0;
	mod2 = 10000;
	list = conf->my_scene.obj_lst;
	obj2 = (t_objet *)list->content;
	res = obj2;
	while (list->content)
	{
		obj2 = (t_objet *)list->content;
		if (obj2->type == 1)
		{
			sphere = (t_sphere *)obj2->objet;
			coords_light = ft_coords_light_sphere(sphere, conf->my_scene.light_lst.pos);
			if (coords_light == 1)
			{
				mod = coords_light;
				if (mod < mod2)
				{
					mod2 = mod;
					res = obj2;
				}
			}
		}
		if (obj2->type == 2)
		{
			cylinder = (t_cylinder *)obj2->objet;
			coords_light = ft_coords_light_cylinder(cylinder, conf->my_scene.light_lst.pos);
			if (coords_light == 1)
			{
				mod = coords_light;
				if (mod < mod2)
				{
					mod2 = mod;
					res = obj2;
				}
			}
		}
		if (obj2->type == 3)
		{
			plane = (t_m_plane *)obj2->objet;
			coords_light = ft_coords_light_plane(plane, conf->my_scene.light_lst.pos);
			if (coords_light == 1)
			{
				mod = coords_light;
				if (mod < mod2)
				{
					mod2 = mod;
					res = obj2;
				}
			}
		}
		list = list->next;
	}
	coords_light = 0;
	if (res->type == obj->type)
	{
		if (obj->type == 1)
		{
			sphere = (t_sphere *)obj->objet;
			coords_light = ft_coords_light_sphere(sphere, conf->my_scene.light_lst.pos);
			if (coords_light == 1)
			{
				sphere2 = (t_sphere *)res->objet;
				if (sphere2->center.x == sphere->center.x
					&& sphere2->center.y == sphere->center.y
					&& sphere2->center.z == sphere->center.z
					&& sphere2->radius == sphere->radius)
					return (1);
			}
		}
		if (obj->type == 2)
		{
			cylinder = (t_cylinder *)obj->objet;
			coords_light = ft_coords_light_cylinder(cylinder, conf->my_scene.light_lst.pos);
			if (coords_light == 1)
			{
				cylinder2 = (t_cylinder *)res->objet;
				if (cylinder2->center.x == cylinder->center.x
					&& cylinder2->center.y == cylinder->center.y
					&& cylinder2->center.z == cylinder->center.z
					&& cylinder2->dir.x == cylinder->dir.x
					&& cylinder2->dir.y == cylinder->dir.y
					&& cylinder2->dir.z == cylinder->dir.z
					&& cylinder2->height == cylinder->height)
					return (1);
			}
		}
		if (obj->type == 3)
		{
			plane = (t_m_plane *)obj->objet;
			coords_light = ft_coords_light_plane(plane, conf->my_scene.light_lst.pos);
			if (coords_light == 1)
			{
				plane2 = (t_m_plane *)res->objet;
				if (plane2->point.x == plane->point.x
					&& plane2->point.y == plane->point.y
					&& plane2->point.z == plane->point.z
					&& plane2->normal.x == plane->normal.x
					&& plane2->normal.y == plane->normal.y
					&& plane2->normal.z == plane->normal.z)
					return (1);
			}
		}
	}
	return (0);
}

void	ft_point(t_objet *obj, t_conf *conf)
{
	double			intensity;
	t_sphere		*aux;
	t_vector		perp;
	t_m_plane		*aux2;
	t_cylinder		*aux3;
	t_rgb			rgb;
	int				tmp;
	int				extra;
	t_vector		auxpoint;
	int				dist;
	t_vector		cnormal;
	double			distance;
	int				buf;

	if (obj->type == 1)
	{
		aux = (t_sphere *)obj->objet;
		perp = normalize(vec(aux->intersection.x - aux->center.x, aux->intersection.y - aux->center.y, aux->intersection.z - aux->center.z));
		buf = ft_light_intersec(obj, conf);
		if (buf == 1)
			intensity = ft_escalar_prod(vec(conf->my_scene.light_lst.pos.x - aux->intersection.x, conf->my_scene.light_lst.pos.y - aux->intersection.y, conf->my_scene.light_lst.pos.z - aux->intersection.z), perp);
		else
			intensity = 0;
		auxpoint = vec(aux->intersection.x - conf->my_scene.light_lst.pos.x, aux->intersection.y - conf->my_scene.light_lst.pos.y, aux->intersection.z - conf->my_scene.light_lst.pos.z);
		distance = sqrt(auxpoint.x * auxpoint.x + auxpoint.y * auxpoint.y + auxpoint.z * auxpoint.z);
		if (intensity < 0)
			intensity = 0;
		rgb.red = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) + (intensity / distance * (conf->my_scene.light_lst.radius))) * aux->color.red;
		if (rgb.red > 255)
			rgb.red = 255;
		rgb.green = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) + (intensity / distance * (conf->my_scene.light_lst.radius))) * aux->color.green;
		if (rgb.green > 255)
            rgb.green = 255;
		rgb.blue = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) + (intensity / distance * (conf->my_scene.light_lst.radius))) * aux->color.blue;
		if (rgb.blue > 255)
            rgb.blue = 255;
		tmp = rgb_to_int(rgb);
		conf->my_pixel.color = tmp;
	}
	else if (obj->type == 2)
	{
		aux3 = (t_cylinder *)obj->objet;
		if (aux3->base.plane_ecuation.x * aux3->intersection.x + aux3->base.plane_ecuation.y * aux3->intersection.y + aux3->base.plane_ecuation.z * aux3->intersection.z == aux3->base.plane_ecuation.x * aux3->base.center.x + aux3->base.plane_ecuation.y * aux3->base.center.y + aux3->base.plane_ecuation.z * aux3->base.center.z)
		{
			buf = ft_light_intersec(obj, conf);
			if (buf == 1)
				intensity = ft_escalar_prod(vec(conf->my_scene.light_lst.pos.x - aux3->intersection.x, conf->my_scene.light_lst.pos.y - aux3->intersection.y, conf->my_scene.light_lst.pos.z - aux3->intersection.z), aux3->base.normal);
			else
				intensity = 0;
			if (intensity < 0)
				intensity = 0;
			rgb.red = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->base.color.red;
			rgb.green = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->base.color.green;
			rgb.blue = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->base.color.blue;
			tmp = rgb_to_int(rgb);
			conf->my_pixel.color = tmp;
		}
		else if (aux3->roof.plane_ecuation.x * aux3->intersection.x + aux3->roof.plane_ecuation.y * aux3->intersection.y + aux3->roof.plane_ecuation.z * aux3->intersection.z == aux3->roof.plane_ecuation.x * aux3->roof.center.x + aux3->roof.plane_ecuation.y * aux3->roof.center.y + aux3->roof.plane_ecuation.z * aux3->roof.center.z)
		{
			buf = ft_light_intersec(obj, conf);
			if (buf == 1)
				intensity = ft_escalar_prod(vec(conf->my_scene.light_lst.pos.x - aux3->intersection.x, conf->my_scene.light_lst.pos.y - aux3->intersection.y, conf->my_scene.light_lst.pos.z - aux3->intersection.z), aux3->roof.normal);
			else
				intensity = 0;
			if (intensity < 0)
				intensity = 0;
			rgb.red = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->roof.color.red;
			rgb.green = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->roof.color.green;
			rgb.blue = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->roof.color.blue;
			tmp = rgb_to_int(rgb);
			conf->my_pixel.color = tmp;
		}
		else
		{
			extra = aux3->base.plane_ecuation.x * aux3->base.center.x + aux3->base.plane_ecuation.y * aux3->base.center.y + aux3->base.plane_ecuation.z * aux3->base.center.z;
			dist = ft_dist_point_plane(aux3->base.plane_ecuation, extra, aux3->intersection);
			auxpoint = vec(aux3->intersection.x + aux3->body.dir.x * dist, aux3->intersection.y + aux3->body.dir.y * dist, aux3->intersection.z + aux3->body.dir.z * dist);
			cnormal = vec(auxpoint.x - aux3->body.center.x, auxpoint.y - aux3->body.center.y, auxpoint.z - aux3->body.center.z);
			buf = ft_light_intersec(obj, conf);
			if (buf == 1)
				intensity = ft_escalar_prod(vec(conf->my_scene.light_lst.pos.x - aux3->intersection.x, conf->my_scene.light_lst.pos.y - aux3->intersection.y, conf->my_scene.light_lst.pos.z - aux3->intersection.z), cnormal);
			else
				intensity = 0;
			if (intensity < 0)
				intensity = 0;
			rgb.red = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->color.red;
			rgb.green = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->color.green;
			rgb.blue = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->color.blue;
			tmp = rgb_to_int(rgb);
			conf->my_pixel.color = tmp;
		}
	}
	else if (obj->type == 3)
	{
		aux2 = (t_m_plane *)obj->objet;
		buf = ft_light_intersec(obj, conf);
		if (buf == 1)
			intensity = ft_escalar_prod(vec(conf->my_scene.light_lst.pos.x - aux2->intersection.x, conf->my_scene.light_lst.pos.y - aux2->intersection.y, conf->my_scene.light_lst.pos.z - aux2->intersection.z), aux2->normal);
		else
			intensity = 0;
		if (intensity < 0)
			intensity = 0;
		rgb.red = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) + intensity * conf->my_scene.light_lst.radius) * aux2->color.red;
		rgb.green = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) + intensity * conf->my_scene.light_lst.radius) * aux2->color.green;
		rgb.blue = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) + intensity * conf->my_scene.light_lst.radius) * aux2->color.blue;
		tmp = rgb_to_int(rgb);
		conf->my_pixel.color = tmp;
	}
}
