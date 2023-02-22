#include "./includes/camera.h"
#include "./includes/color.h"
#include "./includes/file_reader.h"
#include "./includes/geometry.h"
#include "./includes/raytracer.h"
#include "./includes/vector.h"
#include "./includes/ft_process.h"
# include <math.h>

/*t_vector cross_prod(t_vector u, t_vector v)
{
	t_vector w;

	w.x = u.y * v.z - u.z * v.y;
	w.y = -(u.x*v.z - u.z*v.x);
	w.z = u.x * v.y - u.y * v.x;
	return(w);
}

t_vector prod(t_vector u, double lamda)
{
    return (vec(u.x * lamda, u.y * lamda, u.z * lamda));
}

double	limit(double d, double min, double max)
{
	d = (d < min) ? min : d;
	d = (d > max) ? max : d;
	return (d);
}*/

void	camera(char *buf, t_conf *conf)
{
	/*t_screen	my_screen;
	//t_camera	*my_camera;
	double		*param;
	int			mcd;
	double		angle;

	conf->flag.c = 1;
	//my_camera = malloc(sizeof(t_camera));
	param = get_params(buf, 7);
	mcd = ft_mcd(conf->mlx.window_size.x, conf->mlx.window_size.y);
	my_screen.w = conf->mlx.window_size.x / mcd;
	my_screen.h = conf->mlx.window_size.y / mcd;
	angle = limit(param[6], 0, 180);
	angle *= 3.14 / 360.0;
	conf->my_scene.cam_lst.dist = (my_screen.w / 2.0) / tan(angle);
	my_screen.x_axis = normalize(cross_prod(
						vec(param[3], param[4], param[5]), vec(0, 0, -1)));
	my_screen.y_axis = normalize(vec(0, 0, -1));
	my_screen.pos = vec(param[0], param[1], param[2]);
	conf->my_scene.cam_lst.pos = add(prod(normalize(vec(param[3], param[4], param[5])),
				-conf->my_scene.cam_lst.dist), my_screen.pos);
	free(param);
	conf->my_scene.cam_lst.display = my_screen;*/
	double      *param;
	param = get_params(buf, 7);
	conf->my_scene.cam_lst.pos = vec(param[3], param[4], param[5]);
	conf->my_scene.cam_lst.view = vec(param[0], param[1], param[2]);
	conf->my_scene.cam_lst.grades = param[6];
}
