#ifndef FT_PROCESS_H
# define FT_PROCESS_H

t_conf  ft_process(char **buff);
double      *get_params(const char *buf, int size);
t_color     ft_color(double r, double g, double b);
t_vector vec(double x, double y, double z);
long double ft_atod(const char *str);
void		ft_objetinit(double *paramsin, t_objet *obj);
void    camera(char *buf, t_conf *conf);
int		ft_mcd(int a, int b);
t_vector normalize(t_vector u);
t_vector add(t_vector u, t_vector v);
t_vector provec(t_vector u, t_vector v);
int ft_objet(char *buf, t_conf *conf);

#endif
