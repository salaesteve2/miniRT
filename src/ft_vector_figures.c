#include "../includes/minirt.h"
#include "../includes/camera.h"
#include "../includes/color.h"
#include "../includes/file_reader.h"
#include "../includes/geometry.h"
#include "../includes/raytracer.h"
#include "../includes/vector.h"
#include "../includes/ft_process.h"

int	ft_vector_to_sphere(t_vector vision, t_sphere objet)
{

	int distcent;

	distcent = (vision.x * objet->center.x + vision.y * objet->center.y + vision.z * objet->center.z) / sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);

	if (distcent > objet->radius)
		return (0);
	else
		return (1);
}

int	ft_vector_to_cylinder(t_vector vision, t_cylinder objet)
{

}

int ft_vector_to_plane(t_vector vision, t_m_plane objet)
{
	int dis1;
	int dis2;

	t_point *origin;

	origin.x = 0;
	origin.y = 0;
	origin.z = 0;


	 int extra = objet->plane_ecuation.x * objet->point.x + objet->plane_ecuation.y * objet->point.y + objet->plane_ecuation.z * objet->center.z;

	dis1 = ft_dist_point_plane(objet.plane_ecuation, extra, origin);

	origin.x = vision.x;
	origin.y = vision.y;
	origin.z = vision.z;

	dis2 = ft_dist_point_plane(objet.plane_ecuation, extra, origin);

	if (dis1 == dis2)
		return (dis1);
	else
		return (0);
}
