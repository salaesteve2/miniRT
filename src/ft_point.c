/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:45:00 by sasalama          #+#    #+#             */
/*   Updated: 2023/02/28 12:16:33 by sasalama         ###   ########.fr       */
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

double	ft_escalar_prod(t_vector a, t_vector b)
{
	double	res;

	res = a.x * b.x + a.y *b.y + a.z + b.z;
	return (res);
}

double	ft_module(t_vector v)
{
	double	res;

	res = v.x * v.x + v.y * v.y + v.z * v.z;
	res = sqrt(res);
	return (res);

}

double	ft_distance_origin(double x, double y, double z)
{
	double	res;

	res = x * x + y * y + z * z;
	res = sqrt(res);
	return (res);
}

int	rgb_to_int(const t_rgb rgb)
{
	return(rgb.red << 16 | rgb.green << 8 | rgb.blue);
}

void	ft_point(double x, double y, double z, t_objet *obj, t_conf *conf)
{
	double			pe;
	double			pe2;
	double			sen;
	double			sen2;
	int				coordz;
	int				coordy;
	double			intensity;
	t_sphere		*aux;
	t_vector		perp;
	t_vector		origpoint;
	t_m_plane		*aux2;
	t_rgb			rgb;
	unsigned char	tmp;

	if (obj->type == 1)
	{
		aux = (t_sphere *)obj->objet;
		///la normal(vector perpendicular) al punto, se usará para la luz
		perp = vec(x - aux->center.x, y - aux->center.y, z - aux->center.z);
		//el vector del origen/camara al punto, necesario para el tamaño y ubicacion del pixel
		origpoint = vec(x, y, z);
				///producto escalar de vect al obj y eje de pantalla / distancia = seno del angulo de visión.
				/////heidht
		pe = ft_escalar_prod(conf->my_camera.h, origpoint);
		pe2 = ft_escalar_prod(conf->my_camera.w, origpoint);
		sen = pe / (ft_module(origpoint));
		sen2 = pe2 / (ft_module(origpoint));
		coordz = (sen / sin(conf->my_camera.radian)) * 1080;
		if (coordz > 360 || coordz < -360)
			return ;
		coordy = (sen2 / sin(conf->my_camera.radian)) * 1080;
		if (coordy > 540 || coordy < -540)
			return ;
		else
		{
			///put point at coordz coordy of the screen//
			////NO TENEMOS EN CUENTA LA INTERSECCION DE OTROS OBJETOS SOBRE EL VECTOR DE LA LUZ FOCAL; vamos que no hay sombra
			intensity = ft_escalar_prod(vec(x - conf->my_scene.light_lst.pos.x, y - conf->my_scene.light_lst.pos.y, z - conf->my_scene.light_lst.pos.z), perp);
			rgb.red = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) * aux->color.red * intensity;
			rgb.green = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) * aux->color.green * intensity;
			rgb.blue = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) * aux->color.blue * intensity;
			if (conf->my_pixel.x == coordy && conf->my_pixel.y == coordz)
			{
				tmp = (unsigned char)rgb_to_int(rgb);
				conf->my_pixel.color = tmp;
			}
			/// FALTAAA: pintamos pixel con colores red, blue y green en coordy, coordz de la pantalla...
		}
	}
	else if (obj->type == 2)
	{

		////para circulo/base


		//
		//para borde/columna
		//if (
	}
	else if (obj->type == 3)
	{
		aux2 = (t_m_plane *)obj->objet;
		//el vector del origen/camara al punto, necesario para el tamaño y ubicacion del pixel
		origpoint = vec(x, y, z);
				///producto escalar de vect al obj y eje de pantalla / distancia = seno del angulo de visión.
				/////heidht
		pe = ft_escalar_prod(conf->my_camera.h, origpoint);
		pe2 = ft_escalar_prod(conf->my_camera.w, origpoint);
		sen = pe / (ft_module(origpoint));
		sen2 = pe2 / (ft_module(origpoint));
		coordz = (sen / sin(conf->my_camera.radian)) * 1080;
		if (coordz > 360 || coordz < -360)
			return ;
		coordy = (sen2 / sin(conf->my_camera.radian)) * 1080;
		if (coordy > 540 || coordy < -540)
			return ;
		else
		{
			///put point at coordz coordy of the screen//
			////NO TENEMOS EN CUENTA LA INTERSECCION DE OTROS OBJETOS SOBRE EL VECTOR DE LA LUZ FOCAL; vamos que no hay sombras aún
			intensity = ft_escalar_prod(vec(x - conf->my_scene.light_lst.pos.x, y - conf->my_scene.light_lst.pos.y, z - conf->my_scene.light_lst.pos.z), aux2->normal);
			rgb.red = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) * aux2->color.red * intensity;
			rgb.green = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) * aux2->color.green * intensity;
			rgb.blue = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) * aux2->color.blue * intensity;
			/// FALTAAA: pintamos pixel con colores red, blue y green en coordy, coordz de la pantalla...
			if (conf->my_pixel.x == coordy && conf->my_pixel.y == coordz)
			{
				tmp = (unsigned char)rgb_to_int(rgb);
				conf->my_pixel.color = tmp;
			}
		}
	}

}
