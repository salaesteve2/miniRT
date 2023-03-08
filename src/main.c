/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:45:31 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/08 16:06:12 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/geometry.h"

int	ft_errors(int argc, char **argv)
{
	if (argc != 2)
	{
		perror("Error in number of arguments");
		return (1);
	}
	else if (ft_strncmp_rev(argv[1], ".rt", 3))
	{
		perror("Error: Argument must be a '.rt' file");
		return (1);
	}
	return (0);
}

int	ft_parser(char **argv, t_conf *conf)
{
	char		*s;
	char		**lines;
	t_list		*x;
	t_objet		*aux2;
	t_sphere	*a;
	t_cylinder	*c;
	t_m_plane	*b;
	t_objet		*aux;

	s = ft_data(argv);
	if (!s)
	{
		perror("Error in open the file");
		return (1);
	}
	lines = ft_split(s, '\n');
	*conf = ft_process(lines);
	if (conf->flag.error != 0)
	{
		printf("ERROR");
		return (1);
	}
	conf->my_scene.cam_lst.radian = (conf->my_scene.cam_lst.grades * 3.14159265359) / 180;
	conf->my_scene.light_lst.pos.x = conf->my_scene.light_lst.pos.x - conf->my_scene.cam_lst.pos.x;
	conf->my_scene.light_lst.pos.y = conf->my_scene.light_lst.pos.y - conf->my_scene.cam_lst.pos.y;
	conf->my_scene.light_lst.pos.z = conf->my_scene.light_lst.pos.z - conf->my_scene.cam_lst.pos.z;
	x = conf->my_scene.obj_lst;
	while (x->content)
	{
		aux2 = (t_objet *)x->content;
		if (aux2->type == 1)
		{
			a = (t_sphere *)aux2->objet;
			a->center.x = a->center.x - conf->my_scene.cam_lst.pos.x;
			a->center.y = a->center.y - conf->my_scene.cam_lst.pos.y;
			a->center.z = a->center.z - conf->my_scene.cam_lst.pos.z;
		}
		else if (aux2->type == 2)
		{
			c = (t_cylinder *)aux2->objet;
			c->center.x = c->center.x - conf->my_scene.cam_lst.pos.x;
			c->center.y = c->center.y - conf->my_scene.cam_lst.pos.y;
			c->center.z = c->center.z - conf->my_scene.cam_lst.pos.z;
			c->dir = normalize(c->dir);
			c->body.center = c->center;
			c->body.dir = c->dir;
			c->body.color = c->color;
			c->body.height = c->height;
			c->body.radius = c->radius;
			c->base.color = c->color;
			c->roof.color = c->color;
			c->base.radius = c->radius;
			c->base.normal = c->dir;
			c->base.center = vec(c->center.x + c->dir.x * c->height / 2, c->center.y + c->dir.y * c->height / 2, c->center.z + c->dir.z * c->height / 2);
			c->roof.radius = c->radius;
			c->roof.normal = vec((-1) * c->dir.x, (-1) * c->dir.y, (-1) * c->dir.z);
			c->roof.center = vec(c->center.x - c->dir.x * c->height / 2, c->center.y - c->dir.y * c->height / 2, c->center.z - c->dir.z * c->height / 2);
			c->roof.plane_ecuation = vec((c->roof.normal.x * (1 - c->roof.center.x)), (c->roof.normal.y * (1 - c->roof.center.y)), (c->roof.normal.z * (1 - c->roof.center.z)));
			c->base.plane_ecuation = vec((c->base.normal.x * (1 - c->base.center.x)), (c->base.normal.y * (1 - c->base.center.y)), (c->base.normal.z * (1 - c->base.center.z)));
		}
		else if (aux2->type == 3)
		{
			b = (t_m_plane *)aux2->objet;
			b->point.x = b->point.x - conf->my_scene.cam_lst.pos.x;
			b->point.y = b->point.y - conf->my_scene.cam_lst.pos.y;
			b->point.z = b->point.z - conf->my_scene.cam_lst.pos.z;
			b->normal = normalize(b->normal);
			b->plane_ecuation = vec((b->normal.x * (1 - b->point.x)), (b->normal.y * (1 - b->point.y)), (b->normal.z * (1 - b->point.z)));
		}
		x = x->next;
	}
	conf->my_scene.cam_lst.pos.x = 0;
	conf->my_scene.cam_lst.pos.y = 0;
	conf->my_scene.cam_lst.pos.z = 0;
	conf->my_scene.cam_lst.view = normalize(conf->my_scene.cam_lst.view);
	/*conf->my_scene.cam_lst.h =  normalize(provec(conf->my_scene.cam_lst.view, vec(0, 0, 1)));
	conf->my_scene.cam_lst.w =  normalize(provec(conf->my_scene.cam_lst.view, vec(1, 0, 0)));*/
	if (conf->my_scene.cam_lst.view.z > conf->my_scene.cam_lst.view.y || conf->my_scene.cam_lst.view.z > conf->my_scene.cam_lst.view.x)
		conf->my_scene.cam_lst.h = normalize(provec(conf->my_scene.cam_lst.view, vec(1, 0, 0)));
	else if (conf->my_scene.cam_lst.view.y > conf->my_scene.cam_lst.view.x || conf->my_scene.cam_lst.view.y > conf->my_scene.cam_lst.view.z)
		conf->my_scene.cam_lst.h = normalize(provec(conf->my_scene.cam_lst.view, vec(0, 0, 1)));
	else if (conf->my_scene.cam_lst.view.x > conf->my_scene.cam_lst.view.y || conf->my_scene.cam_lst.view.x > conf->my_scene.cam_lst.view.z)
		conf->my_scene.cam_lst.h = normalize(provec(conf->my_scene.cam_lst.view, vec(0, 1, 0)));
	conf->my_scene.cam_lst.w = normalize(provec(conf->my_scene.cam_lst.view, conf->my_scene.cam_lst.h));
	printf("Luz ambient radio: %f\ncolor: %d, %d, %d\n", conf->my_scene.ambient.radius, conf->my_scene.ambient.color.red, conf->my_scene.ambient.color.green, conf->my_scene.ambient.color.blue);
	printf("\nradio de light:%f\nejes x, y, z de light:%f, %f, %f\n", conf->my_scene.light_lst.radius, conf->my_scene.light_lst.pos.x, conf->my_scene.light_lst.pos.y, conf->my_scene.light_lst.pos.z);
	printf("\nCamera grades:%f\n camera radianes: %f\n", conf->my_scene.cam_lst.grades, conf->my_scene.cam_lst.radian);
	printf("Camera view(x,y,z):%f, %f, %f\n", conf->my_scene.cam_lst.view.x, conf->my_scene.cam_lst.view.y, conf->my_scene.cam_lst.view.z);
	printf("Camera position(x,y,z):%f, %f, %f\n", conf->my_scene.cam_lst.pos.x, conf->my_scene.cam_lst.pos.y, conf->my_scene.cam_lst.pos.z);
	printf("Camera vectors h(xyz) w(xyz): %f %f %f , %f %f %f \n", conf->my_scene.cam_lst.h.x, conf->my_scene.cam_lst.h.y, conf->my_scene.cam_lst.h.z, conf->my_scene.cam_lst.w.x, conf->my_scene.cam_lst.w.y, conf->my_scene.cam_lst.w.z);
	x = conf->my_scene.obj_lst;
	while (x->content)
	{
		aux = (t_objet *)x->content;
		printf("\ntype obj: %i\n", aux->type);
		if (aux->type == 1)
		{
			a = (t_sphere *)aux->objet;
			printf("sphereradio: %f\n", a->radius);
			printf("spherecenter (x,y,z): %f,%f,%f\n", a->center.x, a->center.y, a->center.z);
			printf("spherecolor (r,g,b): %i,%i,%i\n", a->color.red, a->color.green, a->color.blue);
		}
		else if (aux->type == 2)
		{
			c = (t_cylinder *)aux->objet;
			printf("cylinder direction vector (x,y,z): %f,%f,%f\n", c->dir.x, c->dir.y, c->dir.z);
			printf("cylinder center (x,y,z): %f,%f,%f\n", c->center.x, c->center.y, c->center.z);
			printf("cylinder radio: %f and height: %f\n", c->radius, c->height);
			printf("cylinder color (r,g,b): %i,%i,%i\n", c->color.red, c->color.green, c->color.blue);
		}
		else if (aux->type == 3)
		{
			b = (t_m_plane *)aux->objet;
			printf("plane normal vector (x,y,z): %f,%f,%f\n", b->normal.x, b->normal.y, b->normal.z);
			printf("plane point (x,y,z): %f,%f,%f\n", b->point.x, b->point.y, b->point.z);
			printf("plane color (r,g,b): %i,%i,%i\n", b->color.red, b->color.green, b->color.blue);
		}
		x = x->next;
	}
	printf("\n");
	return (0);
}

int	main(int argc, char *argv[])
{
	int		x;
	t_conf	conf;

	x = ft_errors(argc, argv);
	if (x == 1)
		return (1);
	x = ft_parser(argv, &conf);
	if (x == 1)
		return (1);
	ft_mlx_init(&conf);
	return (0);
}
