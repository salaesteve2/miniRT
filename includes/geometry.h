#ifndef GEOMETRY_H
# define GEOMETRY_H
# include "vector.h"
# include <stdbool.h>
# include "color.h"
# include "../src/get_next_line/get_next_line.h"
# include "../lib/mlx/mlx.h"
# include "../lib/libft/libft.h"

typedef struct  s_vector
{
    double      x;
    double      y;
    double      z;
}               t_vector;
typedef struct  s_light
{
    t_vector    pos;
    double      radius;
    t_rgb     color;
}               t_light;

typedef struct  s_camera
{
	t_vector	view;
	 t_vector    h;
	  t_vector    w;
    t_vector    pos;
	double		grades;
	double		radian;
   /*	t_screen    display;
    double      dist;*/
}               t_camera;
typedef struct  s_scene
{
    t_light      light_lst;
    t_list      *obj_lst;
    t_camera      cam_lst;
    t_light     ambient;
}               t_scene;

typedef struct  s_screen
{
    t_vector    pos;
    t_vector    x_axis;
    t_vector    y_axis;
    int         h;
    int         w;
}               t_screen;


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
	int	color;

}				t_pixel;
typedef struct  s_conf
{
    t_scene     my_scene;
    t_camera    my_camera;
    t_mlx       mlx;
    t_flag      flag;
	t_pixel		my_pixel;
}               t_conf;


typedef enum    e_geometry{
    NONE, SPHERE, CYLINDER, PLANE
}               t_geometry;

typedef struct  s_sphere
{
    t_vector    center;
    t_vector    intersection;
    double      radius;
    t_rgb     color;
}               t_sphere;


typedef struct  s_circle
{
    t_vector    center;
    double      radius;
    t_vector    normal;
    t_rgb    	color;
    t_vector    plane_ecuation;
}               t_circle;

typedef struct  s_tube
{
    t_vector    center;
    t_vector    dir;
    double      radius;
    double      height;
    t_rgb	     color;
}               t_tube;

typedef struct  s_cylinder
{
    t_vector    dir;
    t_vector    center;
    t_vector    intersection;
    double      radius;
    double      height;
    t_rgb	     color;
    t_circle    base;
    t_circle    roof;
    t_tube      body;
}               t_cylinder;

/*typedef struct  s_line
{
    t_vector    point;
    t_vector    dir;
}               t_line;*/

typedef struct  s_m_plane
{
    t_vector    point;
    t_vector    normal;
	t_vector	plane_ecuation;
    t_vector    intersection;
    t_rgb     color;
}               t_m_plane;

typedef struct  s_objet
{
    void        *objet;
    t_geometry  type;
}               t_objet;

/*typedef struct  s_ray_hit_data
{
    t_vector    hit_point;
    t_geometry  hit_object;
    t_vector    normal;
    t_color     color;
}               t_ray_hit_data;*/

void	ft_point(t_objet *obj, t_conf *conf);
int		rgb_to_int(const t_rgb rgb);
int		ft_impact(t_conf *conf, t_vector vision);
t_objet	*ft_closet(t_conf *conf, t_vector vision);

int     ft_vector_to_plane(t_vector vision, t_m_plane *objet);
int	ft_vector_to_cylinder(t_vector vision, t_cylinder *objet);
int	ft_vector_to_sphere(t_vector vision, t_sphere *objet);
int ft_dist_point_plane(t_vector plane, int extra, t_vector point);
t_vector vec(double x, double y, double z);
t_vector	ft_coords_point_plane(t_m_plane *plane, t_vector line);
double	ft_module(t_vector v);
t_vector	ft_coords_point_sphere(t_vector vision, t_sphere *objet);
#endif
