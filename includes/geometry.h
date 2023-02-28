#ifndef GEOMETRY_H
# define GEOMETRY_H
# include "vector.h"
# include <stdbool.h>
# include "color.h"

typedef enum    e_geometry{
    NONE, SPHERE, CYLINDER, PLANE
}               t_geometry;

typedef struct  s_sphere
{
    t_vector    center;
    double      radius;
    t_rgb     color;
}               t_sphere;

typedef struct  s_cylinder
{
    t_vector    dir;
    t_vector    center;
    double      radius;
    double      height;
    t_rgb     color;
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

#endif
