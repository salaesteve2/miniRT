/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:55:31 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/09 13:34:31 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H
# include <stdbool.h>
# include "../src/get_next_line/get_next_line.h"
# include "../lib/mlx/mlx.h"
# include "../lib/libft/libft.h"
# include <math.h>

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

typedef struct s_rgb
{
	int				red;
	int				green;
	int				blue;
}				t_rgb;

typedef struct s_v
{
    double  x;
    double  y;
    double  z;
}               t_v;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
	t_v	o;
}				t_vector;

typedef struct s_light
{
	t_vector	pos;
	double		radius;
	t_rgb		color;
}				t_light;

typedef struct s_camera
{
	t_vector	view;
	t_vector	h;
	t_vector	w;
	t_vector	pos;
	double		grades;
	double		radian;
}				t_camera;
typedef struct s_scene
{
	t_light		light_lst;
	t_list		*obj_lst;
	t_camera	cam_lst;
	t_light		ambient;
}				t_scene;

typedef struct s_screen
{
	t_vector	pos;
	t_vector	x_axis;
	t_vector	y_axis;
	int			h;
	int			w;
}				t_screen;

typedef struct s_flag
{
	int	save;
	int	r;
	int	c;
	int	error;
	int	no_f;
}				t_flag;

typedef struct s_mlx
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
typedef struct s_conf
{
	t_scene		my_scene;
	t_camera	my_camera;
	t_mlx		mlx;
	t_flag		flag;
	t_pixel		my_pixel;
}				t_conf;

typedef enum e_geometry{
	NONE,	SPHERE,	CYLINDER,	PLANE
}				t_geometry;

typedef struct s_sphere
{
	t_vector	center;
	t_vector	intersection;
	double		radius;
	t_rgb		color;
}				t_sphere;

typedef struct s_circle
{
	t_vector	center;
	double		radius;
	t_vector	normal;
	t_rgb		color;
	t_vector	plane_ecuation;
}				t_circle;

typedef struct s_tube
{
	t_vector	center;
	t_vector	dir;
	double		radius;
	double		height;
	t_rgb		color;
}				t_tube;

typedef struct s_cylinder
{
	t_vector	dir;
	t_vector	center;
	t_vector	intersection;
	double		radius;
	double		height;
	t_rgb		color;
	t_circle	base;
	t_circle	roof;
	t_tube		body;
}				t_cylinder;

typedef struct s_m_plane
{
	t_vector	point;
	t_vector	normal;
	t_vector	plane_ecuation;
	t_vector	intersection;
	t_rgb		color;
}				t_m_plane;

typedef struct s_objet
{
	void		*objet;
	t_geometry	type;
}				t_objet;

void		ft_point(t_objet *obj, t_conf *conf);
int			rgb_to_int(const t_rgb rgb);
int			ft_impact(t_conf *conf, t_vector vision);
t_objet		*ft_closet(t_conf *conf, t_vector vision);
double		dot_prod(t_vector u, t_vector v);
int			ft_vector_to_plane(t_vector vision, t_m_plane *objet);
int			ft_vector_to_cylinder(t_vector vision, t_cylinder *objet);
int			ft_vector_to_sphere(t_vector vision, t_sphere *objet);
int			ft_dist_point_plane(t_vector plane, int extra, t_vector point);
t_vector	vec(double x, double y, double z);
t_vector	ft_coords_point_plane(t_m_plane *plane, t_vector line);
double		ft_module(t_vector v);
t_vector	ft_coords_point_sphere(t_vector vision, t_sphere *objet);
char		*ft_data(char *argv[]);
int			ft_process_range_ambient_light(double *nb);
int			ft_process_range_camara(double *nb);
int			ft_process_range_light(double *nb);
int			ft_process_range_sphere(double *nb);
int			ft_process_range_flat(double *nb);
int			ft_process_range_cylinder(double *nb);
int			ft_strncmp_rev(const char *s1, const char *s2, size_t n);
t_conf		ft_process(char **buff);
double		*get_params(const char *buf, int size);
t_rgb		ft_color(double r, double g, double b);
t_vector	vec(double x, double y, double z);
long double	ft_atod(const char *str);
void		ft_objetinit(double *paramsin, t_objet *obj);
void		camera(char *buf, t_conf *conf);
int			ft_mcd(int a, int b);
t_vector	normalize(t_vector u);
t_vector	add(t_vector u, t_vector v);
t_vector	provec(t_vector u, t_vector v);
int			ft_objet(char *buf, t_conf *conf);
void		ft_mlx_init(t_conf *conf);
double		dot_prod(t_vector u, t_vector v);
double		magnitude(t_vector u);
t_vector	prod(t_vector u, double lamda);
t_vector	add(t_vector u, t_vector v);
t_vector	provec(t_vector u, t_vector v);
t_vector	normalize(t_vector u);
t_sphere	*sphere_init(double *param);
t_cylinder	*cylinder_init(double *param);
t_m_plane	*plane_init(double *param);
void		ft_objetinit(double *paramsin, t_objet *obj);
#endif
