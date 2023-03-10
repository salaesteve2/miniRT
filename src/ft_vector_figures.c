/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_figures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:31:25 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/09 13:32:22 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/geometry.h"

int	ft_vector_to_sphere(t_vector vision, t_sphere *objet)
{
	double		distcent;
	double		aux;
	double		aux2;
	t_vector	preaux;

	preaux.x = (objet->center.y - vision.o.y) * vision.z - (objet->center.z - vision.o.z) * vision.y;
	preaux.y = (objet->center.z - vision.o.z) * vision.x - (objet->center.x - vision.o.x) * vision.z;
	preaux.z = (objet->center.x - vision.o.x) * vision.y - (objet->center.y- vision.o.y) * vision.x;
	aux = sqrt(pow(preaux.x, 2) + pow(preaux.y, 2) + pow(preaux.z, 2));
	if (aux < 0)
		aux *= -1;
	aux2 = sqrt(pow(vision.x, 2) + pow(vision.y, 2) + pow(vision.z, 2));
	distcent = aux / aux2;
	if (distcent < 0)
		distcent *= -1;
	if (distcent > objet->radius)
		return (0);
	return (1);
}

double	ft_proyectvector2(t_vector a, t_vector nor)
{
	return (dot_prod(a, nor) / (ft_module(nor) * ft_module(nor)));
}

t_vector	ft_coords_point_plane3(t_circle *plane, t_vector line)
{
	double		nb;
	double		res;
	t_vector	point;

	nb = -((plane->center.x - line.o.x) * plane->normal.x) - ((plane->center.y - line.o.y) * plane->normal.y) - ((plane->center.z - line.o.z) * plane->normal.z);
	res = -nb / ((line.x * plane->normal.x) + (line.y * plane->normal.y) + (line.z * plane->normal.z));
	point.x = res * line.x;
	point.y = res * line.y;
	point.z = res * line.z;
	return (point);
}

int	ft_vector_to_cylinder(t_vector vision, t_cylinder *objet)
{
	double		disto;
	double		distv;
	double		predis;
	double		extra;
	//double		rad;
	double		distcent;
	double		module;
	double		matrix;
	t_vector	one;
	t_vector	orig;
	t_vector	corda;
	t_vector	cordb;
	t_vector	unify;
	double		modx;
	double		dist2;
	double		dist;
	t_vector	aux;
	t_vector	norm;
	t_vector	normalplane;
	t_vector	pointplane;
	double		dist_p_center;
	t_vector	resultadocambiado;
	t_circle	*p;
	double		tmp;

	extra = objet->dir.x * (objet->center.x - vision.o.x) + objet->dir.y * (objet->center.y - vision.o.y) + objet->dir.z * (objet->center.z - vision.o.z);
	predis = extra;
	if (predis < 0)
		predis *= -1;
	tmp = sqrt(pow(objet->dir.x, 2) + pow(objet->dir.y, 2) + pow(objet->dir.z, 2));
	disto = predis / tmp;
	predis = objet->dir.x * vision.x + objet->dir.y * vision.y + objet->dir.z * vision.z + extra;
	if (predis < 0)
		predis *= -1;
	distv = predis / tmp;
	if (disto > distv)
		return (0);
	one = vision;
	orig = vec(0, 0, 0);
	dist = ft_proyectvector2(one, objet->roof.normal);
	dist2 = ft_proyectvector2(orig, objet->roof.normal);
	if (dist != dist2)
	{
		corda = ft_coords_point_plane3(&objet->base, vision);
		unify = vec(corda.x - (objet->base.center.x - vision.o.x), corda.y - (objet->base.center.y - vision.o.y), corda.z - (objet->base.center.z - vision.o.z));
		modx = sqrt(unify.x * unify.x + unify.y * unify.y + unify.z * unify.z);
		if (modx <= objet->radius)
			return (1);
		cordb = ft_coords_point_plane3(&objet->roof, vision);
		unify = vec(cordb.x - (objet->roof.center.x - vision.o.x), cordb.y - (objet->roof.center.y - vision.o.y), cordb.z - (objet->roof.center.z - vision.o.z));
		modx = sqrt(pow(unify.x, 2) + pow(unify.y, 2) + pow(unify.z, 2));
		if (modx <= objet->radius)
			return (1);
	}
	//rad = sqrt(objet->radius * objet->radius + (objet->height / 2) * (objet->height / 2));
	aux = (vec(vision.y * objet->dir.z - vision.z * objet->dir.y, vision.z * objet->dir.x - vision.x * objet->dir.z, vision.x * objet->dir.y - vision.y * objet->dir.x));
	module = sqrt(pow(aux.x, 2) + pow(aux.y, 2) + pow(aux.z, 2));
	matrix = vision.x * objet->dir.y * (objet->center.z - vision.o.z) - vision.z * objet->dir.y * (objet->center.x - vision.o.x) + vision.y * objet->dir.z * (objet->center.x - vision.o.x) - vision.y * objet->dir.x * (objet->center.z - vision.o.z) + vision.z * objet->dir.x * (objet->center.y - vision.o.y) - vision.x * objet->dir.z * (objet->center.y - vision.o.y);
	if (matrix < 0)
		matrix *= -1;
	distcent = matrix / module;
	if (distcent < 0)
		distcent *= -1;
	if (distcent > objet->radius)
		return (0);
	norm = normalize(provec(objet->dir, vision));
	normalplane = provec(vision, norm);
	pointplane.x = (-1) * (objet->center.x - vision.o.x);
	pointplane.y = (-1) * (objet->center.y - vision.o.y);
	pointplane.z = (-1) * (objet->center.z - vision.o.z);
	p = (t_circle *)malloc(sizeof(t_circle));
	p->center = pointplane;
	p->normal = normalplane;
	resultadocambiado = ft_coords_point_plane3(p, objet->dir);
	dist_p_center = sqrt(pow(resultadocambiado.x, 2) + pow(resultadocambiado.y, 2) + pow(resultadocambiado.z, 2));
	if (dist_p_center > objet->height / 2)
		return (0);
	return (1);
}

double	ft_proyectvector(t_vector a, t_vector nor)
{
	return (dot_prod(a, nor) / (ft_module(nor) * ft_module(nor)));
}

int	ft_vector_to_plane(t_vector vision, t_m_plane *objet)
{
	t_vector	origplane;
	t_vector	noorigiplane;
	double		dist;
	double		dist2;

	origplane.x = objet->point.x - vision.o.x;
	origplane.y = objet->point.y - vision.o.y;
	origplane.z = objet->point.z - vision.o.z;
	noorigiplane = vec(objet->point.x -vision.o.x -  vision.x, objet->point.y - vision.o.y - vision.y, objet->point.z - vision.o.z - vision.z);
	dist = ft_proyectvector(origplane, objet->normal);
	dist2 = ft_proyectvector(noorigiplane, objet->normal);
	if (dist == dist2 || dist < dist2)
		return (0);
	return (1);
}
