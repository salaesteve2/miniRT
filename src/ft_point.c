/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <valarcon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:45:00 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/11 13:22:38 by valarcon         ###   ########.fr       */
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

/*double	ft_distance_origin(double x, double y, double z)
{
	double	res;

	res = x * x + y * y + z * z;
	res = sqrt(res);
	return (res);
}*/

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

void	ft_point(t_objet *obj, t_conf *conf)
{
	double			intensity;
	t_sphere		*aux;
	t_vector		perp;
	t_m_plane		*aux2;
	t_cylinder		*aux3;
	t_rgb			rgb;
	unsigned char	tmp;
	int				extra;
	t_vector		auxpoint;
	int				dist;
	t_vector		cnormal;
	double			distance;

	if (obj->type == 1)
	{
		aux = (t_sphere *)obj->objet;
		perp = normalize(vec(aux->intersection.x - aux->center.x, aux->intersection.y - aux->center.y, aux->intersection.z - aux->center.z));


		intensity = ft_escalar_prod(vec(conf->my_scene.light_lst.pos.x - aux->intersection.x, conf->my_scene.light_lst.pos.y - aux->intersection.y, conf->my_scene.light_lst.pos.z - aux->intersection.z), perp);
		auxpoint = vec(aux->intersection.x - conf->my_scene.light_lst.pos.x, aux->intersection.y - conf->my_scene.light_lst.pos.y, aux->intersection.z - conf->my_scene.light_lst.pos.z);
		distance = sqrt(auxpoint.x * auxpoint.x + auxpoint.y * auxpoint.y + auxpoint.z * auxpoint.z);

		//intensity = 0.5;
		if (intensity < 0)
           intensity = 0;
		rgb.red = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) + (intensity/distance * (conf->my_scene.light_lst.radius)))  * aux->color.red;
		if (rgb.red > 255)
			rgb.red = 255;
		rgb.green = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) + (intensity/distance * (conf->my_scene.light_lst.radius))) * aux->color.green;
		if (rgb.green > 255)
            rgb.green = 255;
		rgb.blue = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) + (intensity/distance * (conf->my_scene.light_lst.radius))) * aux->color.blue;
		if (rgb.blue > 255)
            rgb.blue = 255;
		tmp = (unsigned char)rgb_to_int(rgb);
		conf->my_pixel.color = tmp;
	}
	else if (obj->type == 2)
	{
		aux3 = (t_cylinder *)obj->objet;
		if (aux3->base.plane_ecuation.x * aux3->intersection.x + aux3->base.plane_ecuation.y * aux3->intersection.y + aux3->base.plane_ecuation.z * aux3->intersection.z == aux3->base.plane_ecuation.x * aux3->base.center.x + aux3->base.plane_ecuation.y * aux3->base.center.y + aux3->base.plane_ecuation.z * aux3->base.center.z)
		{
			intensity = ft_escalar_prod(vec(conf->my_scene.light_lst.pos.x - aux3->intersection.x, conf->my_scene.light_lst.pos.y - aux3->intersection.y, conf->my_scene.light_lst.pos.z - aux3->intersection.z), aux3->base.normal);
			//intensity = 0.5;
			if (intensity < 0)
           		intensity = 0;
			rgb.red = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->base.color.red;
			rgb.green = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->base.color.green;
			rgb.blue = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->base.color.blue;
			tmp = (unsigned char)rgb_to_int(rgb);
			conf->my_pixel.color = tmp;
		}
		else if (aux3->roof.plane_ecuation.x * aux3->intersection.x + aux3->roof.plane_ecuation.y * aux3->intersection.y + aux3->roof.plane_ecuation.z * aux3->intersection.z == aux3->roof.plane_ecuation.x * aux3->roof.center.x + aux3->roof.plane_ecuation.y * aux3->roof.center.y + aux3->roof.plane_ecuation.z * aux3->roof.center.z)
		{
			intensity = ft_escalar_prod(vec(conf->my_scene.light_lst.pos.x - aux3->intersection.x, conf->my_scene.light_lst.pos.y - aux3->intersection.y, conf->my_scene.light_lst.pos.z - aux3->intersection.z), aux3->roof.normal);
			//intensity = 0.5;
			if (intensity < 0)
           		intensity = 0;
			rgb.red = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->roof.color.red;
            rgb.green = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->roof.color.green;
            rgb.blue = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->roof.color.blue;
			tmp = (unsigned char)rgb_to_int(rgb);
			conf->my_pixel.color = tmp;
		}
		else
		{
			extra = aux3->base.plane_ecuation.x * aux3->base.center.x + aux3->base.plane_ecuation.y * aux3->base.center.y + aux3->base.plane_ecuation.z * aux3->base.center.z;
			dist = ft_dist_point_plane(aux3->base.plane_ecuation, extra, aux3->intersection);
			auxpoint = vec(aux3->intersection.x + aux3->body.dir.x * dist, aux3->intersection.y + aux3->body.dir.y * dist, aux3->intersection.z + aux3->body.dir.z * dist);
			cnormal = vec(auxpoint.x - aux3->body.center.x, auxpoint.y - aux3->body.center.y, auxpoint.z - aux3->body.center.z);
			intensity = ft_escalar_prod(vec(conf->my_scene.light_lst.pos.x - aux3->intersection.x, conf->my_scene.light_lst.pos.y - aux3->intersection.y, conf->my_scene.light_lst.pos.z - aux3->intersection.z), cnormal);
			if (intensity < 0)
          		 intensity = 0;
			//intensity = 0.5;
			 rgb.red = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->color.red;
            rgb.green = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->color.green;
            rgb.blue = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) + intensity * conf->my_scene.light_lst.radius) * aux3->color.blue;
			tmp = (unsigned char)rgb_to_int(rgb);
			conf->my_pixel.color = tmp;
		}
	}
	else if (obj->type == 3)
	{
		aux2 = (t_m_plane *)obj->objet;

		intensity = ft_escalar_prod(vec(conf->my_scene.light_lst.pos.x - aux2->intersection.x, conf->my_scene.light_lst.pos.y - aux2->intersection.y, conf->my_scene.light_lst.pos.z - aux2->intersection.z), aux2->normal);
	/*	intensity = ft_escalar_prod(vec( aux2->intersection.x - conf->my_scene.light_lst.pos.x,  aux2->intersection.y - conf->my_scene.light_lst.pos.y,  aux2->intersection.z - conf->my_scene.light_lst.pos.z), aux2->normal);*/
		if (intensity < 0)
		   intensity = 0;	

		//intensity = 0.5;
		 rgb.red = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) + intensity * conf->my_scene.light_lst.radius) * aux2->color.red;
            rgb.green = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) + intensity * conf->my_scene.light_lst.radius) * aux2->color.green;
            rgb.blue = ((conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) + intensity * conf->my_scene.light_lst.radius) * aux2->color.blue;
		tmp = (unsigned char)rgb_to_int(rgb);
		conf->my_pixel.color = tmp;
	}
}
