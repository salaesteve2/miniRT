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
	double	distcent;

	distcent = (vision.x * objet->center.x + vision.y * objet->center.y + vision.z * objet->center.z) / sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
	if (distcent > objet->radius)
		return (0);
	else
		return (1);
}


int	ft_vector_to_cylinder(t_vector vision, t_cylinder *objet)
{
	double rad;
    double distcent;
    /*t_vector    c_o;
    t_vector    unify;*/
    double         module;
    double         matrix;
    //double         distancia;
    //double         distcent2;

	//radio de la esfera que abarca todo el cilindro
    rad = sqrt(objet->radius * objet->radius + (objet->height / 2) * (objet->height / 2));

	//distancia entre los dos rectas (direccion cilindro y vision)
	t_vector aux;

	aux = (vec(vision.y * objet->dir.z - vision.z * objet->dir.y, vision.z * objet->dir.x - vision.x * objet->dir.z, vision.x * objet->dir.y - vision.y * objet->dir.x));
	module = sqrt(aux.x * aux.x + aux.y * aux.y + aux.z * aux.z);

	matrix = vision.x * objet->dir.y * objet->center.z - vision.z * objet->dir.y * objet->center.x + vision.y * objet->dir.z * objet->center.x - vision.y * objet->dir.x * objet->center.z + vision.z * objet->dir.x * objet->center.y - vision.x * objet->dir.z * objet->center.y;
	if (matrix < 0)
		matrix *= -1;

    distcent = matrix / module;
    if (distcent > objet->radius)
        return (0);
	aux = vec(objet->center.y * vision.z - objet->center.z * vision.y, objet->center.z * vision.x - objet->center.x * vision.z, objet->center.x * vision.y - objet->center.y * vision.x);
	module = sqrt(aux.x * aux.x + aux.y * aux.y + aux.z * aux.z);
	matrix = sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
	  distcent = module / matrix;
    if (distcent > rad)
        return (0);

	////AQUI SILENCIADAS LAS ESFERAS DE SEGURIDAD
 /*aux = vec((objet->center.y + objet->dir.y * objet->height) * vision.z - (objet->center.z + objet->dir.z * objet->height) * vision.y, (objet->center.z + objet->dir.z * objet->height) * vision.x - (objet->center.x + objet->dir.x * objet->height) * vision.z, (objet->center.x + objet->dir.x * objet->height) * vision.y - (objet->center.y + objet->dir.y * objet->height) * vision.x);
    module = sqrt(aux.x * aux.x + aux.y * aux.y + aux.z * aux.z);
    matrix = sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
      distcent = module / matrix;
	  if (distcent < objet->height / 2)
        return (0);

	   aux = vec((objet->center.y - objet->dir.y * objet->height) * vision.z - (objet->center.z - objet->dir.z * objet->height) * vision.y, (objet->center.z - objet->dir.z * objet->height) * vision.x - (objet->center.x - objet->dir.x * objet->height) * vision.z, (objet->center.x - objet->dir.x * objet->height) * vision.y - (objet->center.y - objet->dir.y * objet->height) * vision.x);
    module = sqrt(aux.x * aux.x + aux.y * aux.y + aux.z * aux.z);
    matrix = sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
      distcent = module / matrix;
      if (distcent < objet->height / 2)
        return (0);*/

   /* else
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
    t_vector     bots;

    tops.x = objet->base.center.x + objet->base.normal.x * objet->height;
    tops.y = objet->base.center.y + objet->base.normal.y * objet->height;
    tops.z = objet->base.center.z + objet->base.normal.z * objet->height;
    bots.x = objet->roof.center.x + objet->roof.normal.x * objet->height;
    bots.y = objet->roof.center.y + objet->roof.normal.y * objet->height;
    bots.z = objet->roof.center.z + objet->roof.normal.z * objet->height;


     distcent2 = (vision.x * tops.x + vision.y * tops.y + vision.z * tops.z) / sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
    if (distcent < objet->height)
        return (0);
    distcent2 = (vision.x * bots.x + vision.y * bots.y + vision.z * bots.z) / sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
    if (distcent < objet->height)
        return (0);*/
	return (1);
}



/*int	ft_vector_to_cylinder(t_vector vision, t_cylinder *objet)
{
	double		 rad;
    double		 distcent;
    t_vector    c_o;
   // t_vector    unify;
   double         module;
   // double         matrix;
    double         distancia;
    double         distcent2;

    rad = sqrt(objet->radius * objet->radius + (objet->height / 2) * (objet->height / 2));

    distcent = (vision.x * objet->center.x + vision.y * objet->center.y + vision.z * objet->center.z) / sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
    if (distcent > rad)
        return (0);
    else
    {
        c_o.x = objet->center.x * (1);
		 c_o.y = objet->center.y * (1);
		  c_o.z = objet->center.z * (1);
		t_vector qp;
	    qp.x = c_o.y * vision.z - c_o.z * vision.y;
	   qp.y =	c_o.z * vision.x - c_o.x * vision.z;
	  qp.z = c_o.x * vision.y - c_o.y * vision.x;
		module = sqrt(qp.x * qp.x + qp.y * qp.y + qp.z * qp.z);
		 double puta = sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
		distancia = module / (puta);

		//printf("mdist:%f, %f\n", distancia, objet->radius);
        
		
		
		
		
		
		 * unify = normalize(vec(vision.y * objet->dir.z -  vision.z * objet->dir.y, vision.z * objet->dir.x - vision.x * objet->dir.z, vision.x * objet->dir.y - vision.y * objet->dir.x));
        module = sqrt(unify.x * unify.x + unify.y * unify.y + unify.z * unify.z);
		printf("\n\n %f, %f , %f , %f , %f ,%f, %f ,%f, %f\n", c_o.x, c_o.y, c_o.z, objet->dir.x, objet->dir.y, objet->dir.z, vision.x, vision.y, vision.z);

        matrix = c_o.x * vision.y * objet->dir.z + c_o.y * vision.z * objet->dir.x + c_o.z * vision.x * objet->dir.y - c_o.x * vision.z * objet->dir.y - c_o.y * vision.x * objet->dir.z  - c_o.z * vision.y * objet->dir.x;
		printf("%f matrix", matrix);

        distancia = matrix / module;

		

		printf("ditancia%f\n%f\n", distancia, objet->radius);
		if (distancia > objet->radius)
            return (0);
		//printf("ditancia%f\n%f\n", distancia, objet->radius);
    }

	t_vector     tops;
    t_vector    bots;

    tops.x = objet->base.center.x + objet->base.normal.x * objet->height;
    tops.y = objet->base.center.y + objet->base.normal.y * objet->height;
    tops.z = objet->base.center.z + objet->base.normal.z * objet->height;
    bots.x = objet->roof.center.x + objet->roof.normal.x * objet->height;
    bots.y = objet->roof.center.y + objet->roof.normal.y * objet->height;
    bots.z = objet->roof.center.z + objet->roof.normal.z * objet->height;


	t_vector qp;
	double puta;
	c_o = tops;

	 qp.x = c_o.y * vision.z - c_o.z * vision.y;
     qp.y =   c_o.z * vision.x - c_o.x * vision.z;
     qp.z = c_o.x * vision.y - c_o.y * vision.x;
     module = sqrt(qp.x * qp.x + qp.y * qp.y + qp.z * qp.z);
     puta = sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
     distcent2 = module / (puta);



    distcent2 = (vision.x * tops.x + vision.y * tops.y + vision.z * tops.z) / sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
    if (distcent2 < objet->height)
        return (0);*/
    /*distcent2 = (vision.x * bots.x + vision.y * bots.y + vision.z * bots.z) / sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);*/
	/* c_o = bots;

     qp.x = c_o.y * vision.z - c_o.z * vision.y;
     qp.y =   c_o.z * vision.x - c_o.x * vision.z;
     qp.z = c_o.x * vision.y - c_o.y * vision.x;
     module = sqrt(qp.x * qp.x + qp.y * qp.y + qp.z * qp.z);
     puta = sqrt(vision.x * vision.x + vision.y * vision.y + vision.z * vision.z);
     distcent2 = module / (puta);
    if (distcent2 < objet->height)
        return (0);
	printf("SI HAY¡¡¡¡¡\n");
	return (1);
}*/

double	ft_proyectvector(t_vector a, t_vector nor)
{
	return (dot_prod(a, nor) / (ft_module(nor) * ft_module(nor)));

}

int	ft_vector_to_plane(t_vector vision, t_m_plane *objet)
{
/*	int		    dis1;
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
		return (0);
	else
		return (1);*/
	t_vector	origplane;
	t_vector	noorigiplane;

	origplane = objet->point;
	noorigiplane = vec(objet->point.x - vision.x, objet->point.y - vision.y, objet->point.z - vision.z);

	double	dist = ft_proyectvector(origplane, objet->normal);
	double	dist2 = ft_proyectvector(noorigiplane, objet->normal);

	if (dist == dist2 || dist < dist2)
		return (0);
	return (1);


}
