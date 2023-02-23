#ifndef FILE_READER_H
# define FILE_READER_H
//# include "../srcs/configuration/gnl/get_next_line.h"
# include "vector.h"
# include "raytracer.h"

typedef struct  s_flag
{
    int     save;
    int     r;
    int     c;
    int     error;
    int     no_f;
}               t_flag;


typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	void		*img;
	char		*img_ptr;

	char		*window_title;
	t_vector	window_size;
	int			bpp;
	int			size_line;
	int			endian;
}				t_mlx;

typedef struct s_pixel
{
	int	x;
	int	y;

}				t_pixel;
typedef struct  s_conf
{
    t_scene     my_scene;
    t_camera    my_camera;
    t_mlx       mlx;
    t_flag      flag;
	t_pixel		my_pixel;
}               t_conf;

#endif
