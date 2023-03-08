/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_impact.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <valarcon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:01:48 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/08 13:11:36 by valarcon         ###   ########.fr       */
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
	t_vector norm;
	t_vector aux;
	//double  path;
	double	dist;
	t_vector	midpoint;
	t_vector two_points;
	int		extra;
	//t_vector	puntovision;
	double      angle;
    double      modvis;
    double      modaux;

	///el vector del punto mas cercano de vision al vector de direccion del cilindro.
	norm = normalize(provec(obj->dir, vision));

	//un vector entre dos puntos de las dos rectas cualesquiera
	two_points = vec(obj->center.x, obj->center.y, obj->center.z);
	//proyectamos este vector sobre el normalizado para hayar la distancia entre los dos mas cercanos de ambas rectas.
	dist = dot_prod(two_points, norm);
	if (dist > obj->radius)
	{
		return (vec(0, 0, 0));
	}

	extra = obj->dir.x * obj->center.x + obj->dir.y * obj->center.y + obj->dir.z * obj->center.z;

	//ahora tengo las ecuaciones de las rectas vision = 0 y obj_>dir = extra;
	//muevo una la distancia en direccion del vector normal que las une.

	aux = vec(obj->dir.x + norm.x * dist, obj->dir.y + norm.y * dist, obj->dir.z + norm.z * dist);

	///asumo el plano (definido por su normal) que contiene el vector de direccion del cilindro y el vector normal a ambos vectores que une los puntos mas cercanos.
	
	
	t_vector normalplane = provec(norm, aux);

	t_vector	pointplane;

	pointplane.x = obj->center.x;
	pointplane.y = obj->center.y;
	pointplane.z = obj->center.z;
///busco su corte con el vector vision

	double k = (normalplane.x * pointplane.x + normalplane.y * pointplane.y + normalplane.z * pointplane.z) / (normalplane.x * vision.x + normalplane.y * vision.y + normalplane.z * vision.z);

	midpoint.x = k * vision.x;
	midpoint.y = k * vision.y;
	midpoint.z = k * vision.z;


	//ahora calculare la distancia del punto medio al borde del cilindro en 2 dimensiones, es decir, sobre el plano de la base....
	//asumo un triangulo rectangulo con lado dist y con hipotenusa radio. busco el lado qe define la distancia desde la proyeccion del punto medio (o mas cercano al eje del cilindro) del vector vision sobre la base; representacion de lo que me he de mover por vision para estar en el borde del cilindro sin tener en cuenta la altura.
	
	double distaux = sqrt(obj->radius * obj->radius - dist * dist);

	///con ese lado y el angulo que forman los dos vectores busco la hipotenusa que forma el triangulo que incluye la altura ganada...
	modvis = sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
                    modaux = sqrt(obj->base.normal.x * obj->base.normal.x + obj->base.normal.y * obj->base.normal.y + obj->base.normal.z * obj->base.normal.z);
        angle = acos((obj->base.normal.x * vision.x + obj->base.normal.y * vision.y + obj->base.normal.z * vision.z) / (modvis * modaux));

		
		angle = atan(dist / obj->radius);

		double	hipotenusa = distaux / sin(angle);

		///ahora si, muevo desde el punto mas cercano al eje del cilindro que tiene el vector vision una cantidad de la hipotenusa hayada, en la dirección opuesta de vision
		t_vector	result;

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

/*{
	(void)obj;
	t_vector	pointbase;
	t_vector	pointroof;
	t_vector	b_center;
	t_vector	r_center;
	int			module1;
	int			module2;
	t_vector	result;
	t_vector	result2;
	t_vector	preresult;
	double		angle;
	double		modvis;
	double		modaux;
	double		catetocont;
	t_vector	aux;
	double		closeaux;

	pointbase = ft_coords_point_plane2(&obj->base, vision);
	pointroof = ft_coords_point_plane2(&obj->roof, vision);
	b_center = vec(pointbase.x - obj->base.center.x, pointbase.y - obj->base.center.y, pointbase.z - obj->base.center.z);
	r_center = vec(pointroof.x - obj->roof.center.x, pointroof.y - obj->roof.center.y, pointroof.z - obj->roof.center.z);
	module1 = sqrt(b_center.x * b_center.x + b_center.y * b_center.y + b_center.z * b_center.z);
	module2= sqrt(r_center.x * r_center.x + r_center.y * r_center.y + r_center.z * r_center.z);
	modvis = sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
	if (module1 < obj->radius)
	{
		result = pointbase;
	}
	else
	{

		            modaux = sqrt(obj->base.normal.x * obj->base.normal.x + obj->base.normal.y * obj->base.normal.y + obj->base.normal.z * obj->base.normal.z);
        angle = acos((obj->base.normal.x * vision.x + obj->base.normal.y * vision.y + obj->base.normal.z * vision.z) / (modvis * modaux));
        catetocont = (module1 - obj->radius) / tan(angle);
        aux = normalize(vec(obj->base.center.x - pointbase.x, obj->base.center.y - pointbase.y, obj->base.center.z - pointbase.z));
        preresult = vec(pointbase.x + (module1 - obj->radius) * aux.x, pointbase.y + (module1 - obj->radius) * aux.y, pointbase.z + (module1 - obj->radius) * aux.z);
		result = vec(preresult.x - catetocont * obj->base.normal.x, preresult.y - catetocont * obj->base.normal.y, preresult.z - catetocont * obj->base.normal.z);

	}
	if (module2 < obj->radius)
    {
		result2 = pointroof;
    }
    else
    {


		    modaux = sqrt(obj->roof.normal.x * obj->roof.normal.x + obj->roof.normal.y * obj->roof.normal.y + obj->roof.normal.z * obj->roof.normal.z);
        angle = acos((obj->roof.normal.x * vision.x + obj->roof.normal.y * vision.y + obj->roof.normal.z * vision.z) / (modvis * modaux));
        catetocont = (module2 - obj->radius) / tan(angle);
        aux = normalize(vec(obj->roof.center.x - pointroof.x, obj->roof.center.y - pointroof.y, obj->roof.center.z - pointroof.z));
        preresult = vec(pointroof.x + (module2 - obj->radius) * aux.x, pointroof.y + (module2 - obj->radius) * aux.y, pointroof.z + (module2 - obj->radius) * aux.z);
		result2 = vec(preresult.x - catetocont * obj->roof.normal.x, preresult.y - catetocont * obj->roof.normal.y, preresult.z - catetocont * obj->roof.normal.z);

    }

	closeaux = result2.x * result2.x + result2.y * result2.y + result2.z * result2.z;
	if (closeaux < result.x * result.x + result.y * result.y + result.z * result.z)
		result = result2;
	return (result);
}*/

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
