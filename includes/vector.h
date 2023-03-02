#ifndef VECTOR_H
# define VECTOR_H

typedef struct  s_vector
{
    double      x;
    double      y;
    double      z;
}               t_vector;

t_vector vec(double x, double y, double z);
#endif
