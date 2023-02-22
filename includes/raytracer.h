#ifndef RAYTRACER_H
# define RAYTRACER_H
# include "geometry.h"
# include "camera.h"
# include "../minirt.h"
# include "../libft/libft.h"

typedef struct  s_light
{
    t_vector    pos;
    double      radius;
    t_color     color;
}               t_light;

typedef struct  s_scene
{
    t_light      light_lst;
    t_list      *obj_lst;
    t_camera      cam_lst;
    t_light     ambient;
}               t_scene;

#endif
