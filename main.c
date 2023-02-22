/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:45:31 by sasalama          #+#    #+#             */
/*   Updated: 2023/02/22 09:37:20 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "./includes/camera.h"
#include "./includes/color.h"
#include "./includes/file_reader.h"
#include "./includes/geometry.h"
#include "./includes/raytracer.h"
#include "./includes/vector.h"
#include "./includes/ft_process.h"

typedef struct		s_img
{
	void			*img;
 	int				bits_per_pixel;
	int				size_line;
	int				endian;
	unsigned char	*data;
}					t_img;

// Creación ventana

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

//

void	ft_free_all(t_s *window, t_img *img)
{
	free(window->mlx);
	free(window->mlx_win);
	free(window);
	free(img);
}

void	ft_make_img(t_img *img, t_conf *conf)
{
	(void)img;
	(void)conf;
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

	s = ft_data(argv);
	if (!s)
	{
		perror("Error in open the file");
		return (1);
	}
	lines = ft_split(s, '\n');
	*conf = ft_process(lines);
	printf("%i\n", conf->flag.error);
	if (conf->flag.error != 0)
	{
		printf("ERROR");
		return (1);
	}
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
