#include "./includes/camera.h"
#include "./includes/color.h"
#include "./includes/file_reader.h"
#include "./includes/geometry.h"
#include "./includes/raytracer.h"
#include "./includes/vector.h"
#include "./includes/ft_process.h"
# include <math.h>


double dot_prod(t_vector u, t_vector v)
{
    return(u.x * v.x + u.y * v.y + u.z * v.z);
}



double magnitude(t_vector u)
{
	return(sqrt(dot_prod(u,u)));
}

t_vector prod(t_vector u, double lamda)
{
	return (vec(u.x * lamda, u.y * lamda, u.z * lamda));
}


t_vector add(t_vector u, t_vector v)
{
	return(vec(u.x + v.x, u.y + v.y, u.z + v.z));
}


t_vector normalize(t_vector u)
{
	return (prod(u, 1.0 / magnitude(u)));
}


t_sphere	*sphere_init(double *param)
{
	t_sphere	*sphere;

	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	sphere->center = vec(param[0], param[1], param[2]);
	sphere->radius = param[3] / 2;
	sphere->color = ft_color(param[4], param[5], param[6]);
	return (sphere);
}

t_cylinder	*cylinder_init(double *param)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	cylinder->center = vec(param[0], param[1], param[2]);
	cylinder->dir = normalize(vec(param[3], param[4], param[5]));
	cylinder->radius = param[6] / 2;
	cylinder->height = param[7];
	cylinder->color = ft_color(param[8], param[9], param[10]);
	return (cylinder);
}

t_m_plane	*plane_init(double *param)
{
	t_m_plane *plane;

	plane = malloc(sizeof(t_m_plane));
	plane->point = vec(param[0], param[1], param[2]);
	plane->normal = normalize(vec(param[3], param[4], param[5]));
	plane->color = ft_color(param[6], param[7], param[8]);
	return (plane);
}

void     ft_objetinit(double *paramsin, t_objet *obj)
{
	if (obj->type == SPHERE)
	{
		obj->objet = (sphere_init(paramsin));
	}
	else if (obj->type == PLANE)
    {
        obj->objet = (plane_init(paramsin));
    }
	else if (obj->type == CYLINDER)
    {
        obj->objet = (cylinder_init(paramsin));
    }
}
