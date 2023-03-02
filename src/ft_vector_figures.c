#include "../includes/minirt.h"
#include "../includes/camera.h"
#include "../includes/color.h"
#include "../includes/file_reader.h"
#include "../includes/geometry.h"
#include "../includes/raytracer.h"
#include "../includes/vector.h"
#include "../includes/ft_process.h"

int	ft_vector_to_sphere(t_vector vision, t_sphere *objet)
{
	int	distcent;

	distcent = (vision.x * objet->center.x + vision.y * objet->center.y + vision.z * objet->center.z) / sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
	if (distcent > objet->radius)
		return (0);
	else
		return (1);
}

int	ft_vector_to_cylinder(t_vector vision, t_cylinder *objet)
{
	    int rad;
    int distcent;
    t_vector    c_o;
    t_vector    unify;
    int         module;
    int         matrix;
    int         distancia;
    int         distcent2;

    rad = sqrt(objet->radius * objet->radius + (objet->height / 2) * (objet->height / 2));

    distcent = (vision.x * objet->center.x + vision.y * objet->center.y + vision.z * objet->center.z) / sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
    if (distcent > rad)
        return (0);
    else
    {
        c_o = objet->center;
        unify = vec(vision.y * objet->dir.z -  vision.z * objet->dir.y, vision.z * objet->dir.x - vision.x * objet->dir.z, vision.x * objet->dir.y - vision.y * objet->dir.x);
        module = sqrt(unify.x * unify.x + unify.y * unify.y + unify.z * unify.z);

        matrix = c_o.x * vision.y * objet->dir.z + c_o.y * vision.z * objet->dir.x + c_o.z * vision.x * objet->dir.y - c_o.x * vision.z * objet->dir.y - c_o.y * vision.x * objet->dir.z  - c_o.z * vision.y * objet->dir.x;

        distancia = matrix / module;

        if (distancia > objet->radius)
            return (0);
    }

	t_vector     tops;
    t_vector    bots;

    tops.x = objet->base.center.x + objet->base.normal.x * objet->height;
    tops.y = objet->base.center.y + objet->base.normal.y * objet->height;
    tops.z = objet->base.center.z + objet->base.normal.z * objet->height;
    bots.x = objet->roof.center.x + objet->roof.normal.x * objet->height;
    bots.y = objet->roof.center.y + objet->roof.normal.y * objet->height;
    bots.z = objet->roof.center.z + objet->roof.normal.z * objet->height;


    distcent2 = (vision.x * tops.x + vision.y * tops.y + vision.z * tops.z) / sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
    if (distcent2 < objet->height)
        return (0);
    distcent2 = (vision.x * bots.x + vision.y * bots.y + vision.z * bots.z) / sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
    if (distcent2 < objet->height)
        return (0);
	return (1);
}

int	ft_vector_to_plane(t_vector vision, t_m_plane *objet)
{
	int		    dis1;
	int		    dis2;
	t_vector    origin;
	int		    extra;

	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	extra = objet->plane_ecuation.x * objet->point.x + objet->plane_ecuation.y * objet->point.y + objet->plane_ecuation.z * objet->point.z;
	dis1 = ft_dist_point_plane(objet->plane_ecuation, extra, origin);
	origin.x = vision.x;
	origin.y = vision.y;
	origin.z = vision.z;
	dis2 = ft_dist_point_plane(objet->plane_ecuation, extra, origin);
	if (dis1 == dis2)
		return (dis1);
	else
		return (0);
}
