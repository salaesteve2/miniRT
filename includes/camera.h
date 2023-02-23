#ifndef CAMERA_H
# define CAMERA_H
# include "vector.h"

typedef struct  s_screen
{
    t_vector    pos;
    t_vector    x_axis;
    t_vector    y_axis;
    int         h;
    int         w;
}               t_screen;

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
#endif
