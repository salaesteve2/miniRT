#ifndef VECTOR_H
# define VECTOR_H

typedef struct  s_vector
{
    double      x;
    double      y;
    double      z;
}               t_vector;

t_vector vec(double x, double y, double z);
//double	ft_escalar_prod(t_vector a, t_vector b);
//t_point ft_intersecction(t_vector plane, t_vector line);
#endif
