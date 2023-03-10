/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:45:00 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/02 18:40:17 by sasalama         ###   ########.fr       */
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

int ft_dist_point_plane(t_vector plane, int extra, t_vector point)
{

    int res = ((plane.x * point.x + plane.y * point.y + plane.z * point.z + extra) / sqrt(plane.x * plane.x + plane.y * plane.y + plane.z * plane.z));
    if (res < 0)
        res *= -1;
    return (res);


}

int	rgb_to_int(const t_rgb rgb)
{
	return(rgb.red << 16 | rgb.green << 8 | rgb.blue);
}
//no funciona, se pasan los pixeles
void	ft_point(t_objet *obj, t_conf *conf)
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
	t_cylinder		*aux3;
	t_rgb			rgb;
	unsigned char	tmp;
	int				 extra;
	t_vector		auxpoint;
	int 			dist;
	t_vector 		cnormal;

	if (obj->type == 1)
	{
		aux = (t_sphere *)obj->objet;
		///la normal(vector perpendicular) al punto, se usar?? para la luz
		perp = vec(aux->intersection.x - aux->center.x, aux->intersection.y - aux->center.y, aux->intersection.z - aux->center.z);
		//el vector del origen/camara al punto, necesario para el tama??o y ubicacion del pixel
		origpoint = vec(aux->intersection.x, aux->intersection.y, aux->intersection.z);
				///producto escalar de vect al obj y eje de pantalla / distancia = seno del angulo de visi??n.
				/////heidht
		pe = ft_escalar_prod(conf->my_camera.h, origpoint);
		pe2 = ft_escalar_prod(conf->my_camera.w, origpoint);
		sen = pe / (ft_module(origpoint));
		sen2 = pe2 / (ft_module(origpoint));
		coordz = (sen / sin(conf->my_camera.radian)) * 540 + 540;
		coordz = coordz - (1080 - 720) / 2;
		if (coordz > 720 || coordz < 0)
			return ;
		coordy = (sen2 / sin(conf->my_camera.radian)) * 540 + 540;
		if (coordy > 1080 || coordy < 0)
			return ;
		else
		{
			///put point at coordz coordy of the screen//
			////NO TENEMOS EN CUENTA LA INTERSECCION DE OTROS OBJETOS SOBRE EL VECTOR DE LA LUZ FOCAL; vamos que no hay sombra
			intensity = ft_escalar_prod(vec(aux->intersection.x - conf->my_scene.light_lst.pos.x, aux->intersection.y - conf->my_scene.light_lst.pos.y, aux->intersection.z - conf->my_scene.light_lst.pos.z), perp);
			rgb.red = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) * aux->color.red * intensity;
			rgb.green = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) * aux->color.green * intensity;
			rgb.blue = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) * aux->color.blue * intensity;
			tmp = (unsigned char)rgb_to_int(rgb);
			conf->my_pixel.color = tmp;
			/// FALTAAA: pintamos pixel con colores red, blue y green en coordy, coordz de la pantalla...
		}
	}
	else if (obj->type == 2)
	{
		////para circulo/base
		aux3 = (t_cylinder *)obj->objet;
            ////para circulo/base
		if (aux3->base.plane_ecuation.x * aux3->intersection.x + aux3->base.plane_ecuation.y * aux3->intersection.y + aux3->base.plane_ecuation.z * aux3->intersection.z == 0)
		{
			origpoint = vec(aux3->intersection.x, aux3->intersection.y, aux3->intersection.z);
			pe = ft_escalar_prod(conf->my_camera.h, origpoint);
			pe2 = ft_escalar_prod(conf->my_camera.w, origpoint);
			sen = pe / (ft_module(origpoint));
			sen2 = pe2 / (ft_module(origpoint));
			coordz = (sen / sin(conf->my_camera.radian)) * 540 + 540;
			coordz = coordz - (1080 - 720) / 2;
			if (coordz > 720 || coordz < 0)
				return ;
			coordy = (sen2 / sin(conf->my_camera.radian)) * 540 + 540;
			if (coordy > 1080 || coordy < 0)
				return ;
			else
			{
				////NO TENEMOS EN CUENTA LA INTERSECCION DE OTROS OBJETOS SOBRE EL VECTOR DE LA LUZ FOCAL; vamos que no hay sombras a??n
				intensity = ft_escalar_prod(vec(aux3->intersection.x - conf->my_scene.light_lst.pos.x, aux3->intersection.y - conf->my_scene.light_lst.pos.y, aux3->intersection.z - conf->my_scene.light_lst.pos.z), aux3->base.normal);
				rgb.red = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) * aux3->base.color.red * intensity;
				rgb.green = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) * aux3->base.color.green * intensity;
				rgb.blue = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) * aux3->base.color.blue * intensity;
				tmp = (unsigned char)rgb_to_int(rgb);
				conf->my_pixel.color = tmp;
					/// FALTAAA: pintamos pixel con colores red, blue y green en coordy, coordz de la pantalla...
			}
		}
		else if (aux3->roof.plane_ecuation.x * aux3->intersection.x + aux3->roof.plane_ecuation.y * aux3->intersection.y + aux3->roof.plane_ecuation.z * aux3->intersection.z == 0)
		{
			origpoint = vec(aux3->intersection.x, aux3->intersection.y, aux3->intersection.z);
			pe = ft_escalar_prod(conf->my_camera.h, origpoint);
			pe2 = ft_escalar_prod(conf->my_camera.w, origpoint);
			sen = pe / (ft_module(origpoint));
			sen2 = pe2 / (ft_module(origpoint));
			coordz = (sen / sin(conf->my_camera.radian)) * 540 + 540;
			coordz = coordz - (1080 - 720) / 2;
			if (coordz > 720 || coordz < 0)
				return ;
			coordy = (sen2 / sin(conf->my_camera.radian)) * 540 + 540;
			if (coordy > 1080 || coordy < 0)
				return ;
			else
			{
				intensity = ft_escalar_prod(vec(aux3->intersection.x - conf->my_scene.light_lst.pos.x, aux3->intersection.y - conf->my_scene.light_lst.pos.y, aux3->intersection.z - conf->my_scene.light_lst.pos.z), aux3->roof.normal);
				rgb.red = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) * aux3->roof.color.red * intensity;
				rgb.green = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) * aux3->roof.color.green * intensity;
				rgb.blue = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) * aux3->roof.color.blue * intensity;
				tmp = (unsigned char)rgb_to_int(rgb);
				conf->my_pixel.color = tmp;
				/// FALTAAA: pintamos pixel con colores red, blue y green en coordy, coordz de la pantalla...
			}
		}
		else
		{
			extra = aux3->base.plane_ecuation.x * aux3->base.center.x + aux3->base.plane_ecuation.y * aux3->base.center.y + aux3->base.plane_ecuation.z * aux3->base.center.z;
			dist = ft_dist_point_plane(aux3->base.plane_ecuation, extra, aux3->intersection);
			auxpoint = vec(aux3->intersection.x + aux3->body.dir.x * dist, aux3->intersection.y + aux3->body.dir.y * dist, aux3->intersection.z + aux3->body.dir.z * dist);
			cnormal = vec(auxpoint.x - aux3->body.center.x, auxpoint.y - aux3->body.center.y, auxpoint.z - aux3->body.center.z);
			origpoint = vec(aux3->intersection.x, aux3->intersection.y, aux3->intersection.z);
			pe = ft_escalar_prod(conf->my_camera.h, origpoint);
			pe2 = ft_escalar_prod(conf->my_camera.w, origpoint);
			sen = pe / (ft_module(origpoint));
			sen2 = pe2 / (ft_module(origpoint));
			coordz = (sen / sin(conf->my_camera.radian)) * 540 + 540;
			coordz = coordz - (1080 - 720) / 2;
			if (coordz > 720 || coordz < 0)
				return ;
			coordy = (sen2 / sin(conf->my_camera.radian)) * 540 + 540;
			if (coordy > 1080 || coordy < 0)
				return ;
			else
			{
				intensity = ft_escalar_prod(vec(aux3->intersection.x - conf->my_scene.light_lst.pos.x, aux3->intersection.y - conf->my_scene.light_lst.pos.y, aux3->intersection.z - conf->my_scene.light_lst.pos.z), cnormal);
				rgb.red = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) * aux3->color.red * intensity;
				rgb.green = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) * aux3->color.green * intensity;
				rgb.blue = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) * aux3->color.blue * intensity;
				tmp = (unsigned char)rgb_to_int(rgb);
				conf->my_pixel.color = tmp;
			}
		}
	}
	else if (obj->type == 3)
	{
		aux2 = (t_m_plane *)obj->objet;
		//el vector del origen/camara al punto, necesario para el tama??o y ubicacion del pixel
		origpoint = vec(aux2->intersection.x, aux2->intersection.y, aux2->intersection.z);
				///producto escalar de vect al obj y eje de pantalla / distancia = seno del angulo de visi??n.
				/////heidht
		pe = ft_escalar_prod(conf->my_camera.h, origpoint);
		pe2 = ft_escalar_prod(conf->my_camera.w, origpoint);
		sen = pe / (ft_module(origpoint));
		sen2 = pe2 / (ft_module(origpoint));
		coordz = (sen / sin(conf->my_camera.radian)) * 540 + 540;
		coordz = coordz - (1080 - 720) / 2;
		if (coordz > 720 || coordz < 0)
			return ;
		coordy = (sen2 / sin(conf->my_camera.radian)) * 540 + 540;
		if (coordy > 1080 || coordy < 0)
			return ;
		else
		{
			///put point at coordz coordy of the screen//
			////NO TENEMOS EN CUENTA LA INTERSECCION DE OTROS OBJETOS SOBRE EL VECTOR DE LA LUZ FOCAL; vamos que no hay sombras a??n
			intensity = ft_escalar_prod(vec(aux2->intersection.x - conf->my_scene.light_lst.pos.x, aux2->intersection.y - conf->my_scene.light_lst.pos.y, aux2->intersection.z - conf->my_scene.light_lst.pos.z), aux2->normal);
			rgb.red = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.red / 255) * aux2->color.red * intensity;
			rgb.green = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.green / 255) * aux2->color.green * intensity;
			rgb.blue = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.blue / 255) * aux2->color.blue * intensity;
			/// FALTAAA: pintamos pixel con colores red, blue y green en coordy, coordz de la pantalla...
			tmp = (unsigned char)rgb_to_int(rgb);
			conf->my_pixel.color = tmp;
		}
	}
}
