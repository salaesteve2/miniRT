/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:55:08 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/10 11:05:51 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/geometry.h"

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
	int				s;
	double			vecg;
	double			vecp;
	t_vector		vision;
	int				sign;
	double			aux;
	int				aux2;
	double			ay;
	double			ax;

	tab = (void *)img->data;
	conf->my_pixel.x = 0;
	conf->my_scene.cam_lst.view = normalize(conf->my_scene.cam_lst.view);
	ax = sqrt((1080 * 1080) / 2);
	ay = ax * 36 / 54;

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
		vecg = (aux / 540) * /*tan(conf->my_scene.cam_lst.radian)) **/ sign;
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
			vecp = (aux / 360) * /*tan(conf->my_scene.cam_lst.radian)) **/ sign;
			/*double pr = vecp;
			vecp = vecg;
			vecg = pr;*/

		/*	vision = normalize(vec(conf->my_scene.cam_lst.view.x * 2  + conf->my_scene.cam_lst.h.x * vecp + conf->my_scene.cam_lst.w.x * vecg, conf->my_scene.cam_lst.view.y * 2 + conf->my_scene.cam_lst.h.y * vecp + conf->my_scene.cam_lst.w.y * vecg, conf->my_scene.cam_lst.view.z * 2 + conf->my_scene.cam_lst.h.z * vecp + conf->my_scene.cam_lst.w.z * vecg));*/


		/*	t_vector puta;
			puta = vec(conf->my_scene.cam_lst.h.x * vecp + conf->my_scene.cam_lst.w.x * vecg, conf->my_scene.cam_lst.h.y * vecp + conf->my_scene.cam_lst.w.y * vecg, conf->my_scene.cam_lst.h.z * vecp + conf->my_scene.cam_lst.w.z * vecg);
			vision = normalize(vec(conf->my_scene.cam_lst.view.x + puta.x, conf->my_scene.cam_lst.view.y + puta.y, conf->my_scene.cam_lst.view.z + puta.z));*/
			//vision = normalize(vec(vision.x * vision.x, vision.y * vision.y, vision.z * vision.z));
			//vecg = vecp;
			vision = normalize(conf->my_scene.cam_lst.view);
			vision.o.x = conf->my_scene.cam_lst.h.x * ay * (conf->my_scene.cam_lst.radian/1.5708) * vecp + conf->my_scene.cam_lst.w.x * ax * (conf->my_scene.cam_lst.radian/1.5708) * vecg; 
			vision.o.y = conf->my_scene.cam_lst.h.y * ay * (conf->my_scene.cam_lst.radian/1.5708) * vecp + conf->my_scene.cam_lst.w.y * ax * (conf->my_scene.cam_lst.radian/1.5708) * vecg;
			vision.o.z = conf->my_scene.cam_lst.h.z * ay * (conf->my_scene.cam_lst.radian/1.5708) * vecp + conf->my_scene.cam_lst.w.z * ax * (conf->my_scene.cam_lst.radian/1.5708) * vecg;


			if (ft_impact(conf, vision) == 1)
			{
				/*if (conf->my_pixel.y == 360 && conf->my_pixel.x == 540)
					printf("hgafsdg");*/
				obj = ft_closet(conf, vision);
				if (obj)
				{
					//// ?¿?¿conf->my_camera.view.o = vision.o;
					ft_point(obj, conf);
				}
			}
			else
			{
				s = rgb_to_int(conf->my_scene.ambient.color);
				conf->my_pixel.color = s;
			}
			if (conf->my_pixel.y == 360 && conf->my_pixel.x == 540)
			{
				aux2 = ft_impact(conf, vision);
				//printf("pixel enmedio: %i\n %i\ni vision: %f %f %f \n", conf->my_pixel.color, aux2, vision.x, vision.y, vision.z);
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
	img->img = mlx_new_image(window->mlx, 1080, 720);
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
