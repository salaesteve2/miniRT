/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:45:31 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/08 10:54:22 by valarcon         ###   ########.fr       */
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

typedef struct s_img
{
	void			*img;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	unsigned char	*data;
}				t_img;

typedef struct s_s
{
	void	*mlx;
	void	*mlx_win;
}				t_s;

int	ft_exit_hook(t_s *window)
{
	mlx_destroy_window(window->mlx, window->mlx_win);
	exit(-1);
}

int	key_hook(int keycode, t_s *window)
{
	if (keycode == 53)
		ft_exit_hook(window);
	return (0);
}

void	ft_free_all(t_s *window, t_img *img)
{
	free(window->mlx);
	free(window->mlx_win);
	free(window);
	free(img->img);
	free(img->data);
	free(img);
}

void	ft_make_img(t_img *img, t_conf *conf)
{
	int				(*tab)[1080][1];
	t_objet			*obj;
//	t_list			*tmp;
//	t_point			*point;
	int				s;
	double			vecg;
	double			vecp;
	t_vector		vision;
	int				sign;
	double			aux;

	tab = (void *)img->data;
	conf->my_pixel.x = 0;
	//point = malloc(sizeof(double) * 3);
	while (conf->my_pixel.x < 1080)
	{
		aux = (conf->my_pixel.x - 540);
		 if (aux < 0)
             {
                 sign = -1;
                 aux *= -1;
             }
             else
                 sign = 1;
		vecg = (aux / 540) * tan(conf->my_scene.cam_lst.radian) * sign;
		conf->my_pixel.y = 0;
		while (conf->my_pixel.y < 720)
		{
			aux = (conf->my_pixel.y - 360);
			 if (aux < 0)
			 {
				 sign = -1;
				 aux *= -1;
			 }
			 else
				 sign = 1;

			vecp = (aux / 540)  * tan(conf->my_scene.cam_lst.radian) * sign;

			vision = normalize(vec(conf->my_scene.cam_lst.view.x + conf->my_scene.cam_lst.h.x * vecp + conf->my_scene.cam_lst.w.x * vecg, conf->my_scene.cam_lst.view.y + conf->my_scene.cam_lst.h.y * vecp + conf->my_scene.cam_lst.w.y * vecg, conf->my_scene.cam_lst.view.z + conf->my_scene.cam_lst.h.z * vecp + conf->my_scene.cam_lst.w.z * vecg));

			//////A PARTIR DE AQUI DA FLOATING POINT EXCEPTION ERROR
			if (ft_impact(conf, vision) == 1)
			{
				if (conf->my_pixel.y == 360 && conf->my_pixel.x == 540)
					printf("hgafsdg");
				obj = ft_closet(conf, vision);
				if (obj != NULL)
					ft_point(obj, conf);
				//////
			}
			else
			{
				s = rgb_to_int(conf->my_scene.ambient.color);
				conf->my_pixel.color = s;
			}


			if (conf->my_pixel.y == 360 && conf->my_pixel.x == 540)
			{
				int aux = ft_impact(conf, vision);
				printf("pixel enmedio: %i\n %i\ni vision: %f %f %f \n", conf->my_pixel.color, aux, vision.x, vision.y, vision.z);
			}


			*tab[conf->my_pixel.y][conf->my_pixel.x] = conf->my_pixel.color;
			conf->my_pixel.y++;
		}
		conf->my_pixel.x++;
	}
}

void	ft_mlx_init(t_conf *conf)
{
	t_s		*window;
	t_img	*img;

	img = malloc(sizeof(*img));
	window = malloc(sizeof(*window));
	window->mlx = mlx_init();
	img->img = mlx_new_image(window->mlx, 1080, 720); //struct para cambiar resolucion, o variable
	img->data = (unsigned char *)mlx_get_data_addr(img->img, &(img->bits_per_pixel), &(img->size_line), &(img->endian));
	ft_make_img(img, conf);
	window->mlx_win = mlx_new_window(window->mlx, 1080, 720, "MiniRT");
	mlx_put_image_to_window(window->mlx, window->mlx_win, img->img, 0, 0);
	mlx_destroy_image(window->mlx, img->img);
	mlx_key_hook(window->mlx_win, key_hook, window);
	mlx_hook(window->mlx_win, 17, 1L << 17, ft_exit_hook, window);
	mlx_loop(window->mlx);
	ft_free_all(window, img);
}

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
	char	*s;
	char	**lines;
	t_list	*x;

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

	////PRINTEO AUXILIAR////
	conf->my_scene.cam_lst.radian = (conf->my_scene.cam_lst.grades * 3.14159265359) / 180;
	conf->my_scene.light_lst.pos.x = conf->my_scene.light_lst.pos.x - conf->my_scene.cam_lst.pos.x;
	conf->my_scene.light_lst.pos.y = conf->my_scene.light_lst.pos.y - conf->my_scene.cam_lst.pos.y;
	conf->my_scene.light_lst.pos.z = conf->my_scene.light_lst.pos.z - conf->my_scene.cam_lst.pos.z;

	x = conf->my_scene.obj_lst;
    while (x->content)
    {
        t_objet *aux =  (t_objet *)x->content;
        if (aux->type == 1)
        {
            t_sphere    *a = (t_sphere *)aux->objet;
            a->center.x = a->center.x - conf->my_scene.cam_lst.pos.x;
			a->center.y = a->center.y - conf->my_scene.cam_lst.pos.y;
			a->center.z = a->center.z - conf->my_scene.cam_lst.pos.z;
        }
        else if (aux->type == 2)
        {
			t_cylinder    *c = (t_cylinder *)aux->objet;
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
                            ///tal que el punto x,y,z estará en el plano de roof si x* plane_ecuation.x + y*planeecuation.y + z*planeecuat.z == 0
            c->base.plane_ecuation = vec((c->base.normal.x * (1 - c->base.center.x)), (c->base.normal.y * (1 - c->base.center.y)), (c->base.normal.z * (1 - c->base.center.z)));
        }
        else if (aux->type == 3)
        {
            t_m_plane    *b = (t_m_plane *)aux->objet;
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
	conf->my_scene.cam_lst.h =  normalize(provec(conf->my_scene.cam_lst.view, vec(0, 0, 1)));
	 conf->my_scene.cam_lst.w =  normalize(provec(conf->my_scene.cam_lst.view, vec(1, 0, 0)));

	
	//
	printf("Luz ambient radio: %f\ncolor: %d, %d, %d\n", conf->my_scene.ambient.radius, conf->my_scene.ambient.color.red, conf->my_scene.ambient.color.green, conf->my_scene.ambient.color.blue);
	printf("\nradio de light:%f\nejes x, y, z de light:%f, %f, %f\n", conf->my_scene.light_lst.radius, conf->my_scene.light_lst.pos.x, conf->my_scene.light_lst.pos.y, conf->my_scene.light_lst.pos.z);
	printf("\nCamera grades:%f\n camera radianes: %f\n", conf->my_scene.cam_lst.grades, conf->my_scene.cam_lst.radian);
	printf("Camera view(x,y,z):%f, %f, %f\n", conf->my_scene.cam_lst.view.x, conf->my_scene.cam_lst.view.y, conf->my_scene.cam_lst.view.z);
	printf("Camera position(x,y,z):%f, %f, %f\n", conf->my_scene.cam_lst.pos.x, conf->my_scene.cam_lst.pos.y, conf->my_scene.cam_lst.pos.z);
	 printf("Camera vectors h(xyz) w(xyz): %f %f %f , %f %f %f \n", conf->my_scene.cam_lst.h.x, conf->my_scene.cam_lst.h.y, conf->my_scene.cam_lst.h.z, conf->my_scene.cam_lst.w.x, conf->my_scene.cam_lst.w.y, conf->my_scene.cam_lst.w.z);

	x = conf->my_scene.obj_lst;
	while (x->content)
	{
		t_objet *aux =  (t_objet *)x->content;
		printf("\ntype obj: %i\n", aux->type);
		if (aux->type == 1)
		{
			t_sphere	*a = (t_sphere *)aux->objet;
			printf("sphereradio: %f\n", a->radius);
			printf("spherecenter (x,y,z): %f,%f,%f\n", a->center.x, a->center.y, a->center.z);
			printf("spherecolor (r,g,b): %i,%i,%i\n", a->color.red, a->color.green, a->color.blue);
		}
		else if (aux->type == 2)
        {
            t_cylinder    *c = (t_cylinder *)aux->objet;
            printf("cylinder direction vector (x,y,z): %f,%f,%f\n", c->dir.x, c->dir.y, c->dir.z);
            printf("cylinder center (x,y,z): %f,%f,%f\n", c->center.x, c->center.y, c->center.z);
			printf("cylinder radio: %f and height: %f\n", c->radius, c->height);
            printf("cylinder color (r,g,b): %i,%i,%i\n", c->color.red, c->color.green, c->color.blue);
        }
		else if (aux->type == 3)
        {
            t_m_plane    *b = (t_m_plane *)aux->objet;
            printf("plane normal vector (x,y,z): %f,%f,%f\n", b->normal.x, b->normal.y, b->normal.z);
            printf("plane point (x,y,z): %f,%f,%f\n", b->point.x, b->point.y, b->point.z);
            printf("plane color (r,g,b): %i,%i,%i\n", b->color.red, b->color.green, b->color.blue);
		}
		x = x->next;
	}
	printf("\n");

	////
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
