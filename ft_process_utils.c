#include "./includes/camera.h"
#include "./includes/color.h"
#include "./includes/file_reader.h"
#include "./includes/geometry.h"
#include "./includes/raytracer.h"
#include "./includes/vector.h"

int     nbrlen(long nb)
{
    int     len;

    len = 0;
    if (nb <= 0)
    {
        nb = nb * -1;
        len++;
    }
    while (nb > 0)
    {
        nb = nb / 10;
        len++;
    }
    return (len);
}

int ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    else
        return (0);
}

int     ft_atoi(const char *str)
{
    int                 i;
    int                 a;
    unsigned long long  num;

    i = 0;
    num = 0;
    a = 1;
    while (str[i] != '\0' && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
        i++;
    if (str[i] == '-' || str[i] == '+')
        if (str[i++] == '-')
            a = a * -1;
    while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
    {
        if (num > __LONG_LONG_MAX__ || i >= 19)
            return (a == -1 ? 0 : -1);
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return (num * a);
}

long double ft_atod(const char *str)
{
    int             i;
    long double     intg;
    long double     dec;
    int             sign;
    int             z_len;

    i = 0;
    dec = 0;
    sign = 1;
    z_len = 0;
    while (!(ft_isdigit(str[i])))
    {
        sign = (str[i] == '-') ? sign * -1 : sign;
        i++;
    }
    intg = ft_atoi(str + i);
    i += nbrlen(intg);
    if (str[i] == '.')
    {
        i++;
        dec = ft_atoi(str + i);
        while (str[i++] == '0')
            z_len++;
    }
    return (intg * sign + (dec / pow(10, nbrlen(dec) + z_len)) * sign);
}

double      *get_params(const char *buf, int size)
{
    double      *param;
    int         pos;
    int         l;

    pos = 0;
    l = 0;
    param = (double *)malloc(sizeof(double) * (size));
    while (buf[pos])
    {
        if ((ft_isdigit(buf[pos]) || buf[pos] == '-') && l < size)
        {
            param[l] = ft_atod(&buf[pos]);
            l++;
            while ((buf[pos]) != 32 && buf[pos] != ',' && buf[pos])
                pos++;
			if (size == l && buf[pos - 1] == '\0')
				break;
			else if (size == l)
			{
				while (buf[pos] && buf[pos] == 32)
					pos++;
				if (buf[pos] == '\0')
					break;
				else
				{
					 free (param);
       				 param = NULL;
					 return (param);
				}
			}
        }
        pos++;
    }
 	if (size > l)
    {
        free (param);
        param = NULL;
    }
    return (param);
}

/*double      *get_params(const char *buf, int size)
{
    double      *param;
    int         pos;
    int         l;

	printf("%s\n\n", buf);
    pos = 0;
    l = 0;
    param = (double *)malloc(sizeof(double) * (size));
    while (buf[pos] && buf[pos] != '\0')
    {
		printf(":%c\n", buf[pos]);
        if ((ft_isdigit(buf[pos]) || buf[pos] == '-'))
        {
			if ((l == size || l > size) && buf[pos] != ' ')
			{
				free (param);
        param = NULL;
 printf("asdfkafgkgf%c\n", buf[pos]);
		return (param);
			}
            param[l] = ft_atod(&buf[pos]);
            l++;
            while ((buf[pos]) != 32 && buf[pos] != ',' && buf[pos])
                pos++;
        }
	*if (buf[pos] && buf[pos] != ' ' && buf[pos] != '\n' && (ft_isdigit(buf[pos]) || buf[pos] == '-') && l == size)
        {
			printf("bufpos%c\n", buf[pos]);
            l++;
        }
        pos++;
    }
	if (size != l)
	{
		free (param);
		param = NULL;
	}
	printf("%isizei\n%iele\n", size, l);
    return (param);
}*/

t_color     ft_color(double r, double g, double b)
{
    t_color     color;

    color.r = r;
    color.g = g;
    color.b = b;
    return (color);
}

t_vector vec(double x, double y, double z)
{
    t_vector out;
    out.x = x;
    out.y = y;
    out.z = z;

    return (out);
}

/*int		ft_mcd(int a, int b)
{
	int c;

	c = 1;
	while (b != 0)
	{
		c = b;
		b = a % b;
		a = c;
	}
	return (c);
}*/
