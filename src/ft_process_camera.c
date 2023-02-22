#include "../includes/camera.h"
#include "../includes/color.h"
#include "../includes/file_reader.h"
#include "../includes/geometry.h"
#include "../includes/raytracer.h"
#include "../includes/vector.h"
#include "../includes/ft_process.h"
#include "../includes/minirt.h"

void	camera(char *buf, t_conf *conf)
{
	double      *param;
	param = get_params(buf, 7);
	conf->my_scene.cam_lst.pos = vec(param[3], param[4], param[5]);
	conf->my_scene.cam_lst.view = vec(param[0], param[1], param[2]);
	conf->my_scene.cam_lst.grades = param[6];
}
