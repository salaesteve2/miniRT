#include "../includes/camera.h"
#include "../includes/color.h"
#include "../includes/file_reader.h"
#include "../includes/geometry.h"
#include "../includes/raytracer.h"
#include "../includes/vector.h"
#include "../includes/ft_process.h"

int ft_ambient(char *buff, t_scene *s_scene)
{
    double *params;


    /*if (s_scene->ambient.radius != 0 || s_scene->ambient.color.red != 0 || s_scene->ambient.color.green != 0 || s_scene->ambient.color.blue != 0)
    {
        return (2);
    }*/
    params = get_params(buff, 4);
	 if (params == NULL)
        return (1);
    if (ft_process_range_ambient_light(params) == 1)
    {
        free(params);
        return (1);
    }
    else
    {
        s_scene->ambient.radius = params[0];
        s_scene->ambient.color = ft_color(params[1], params[2], params[3]);
    }
    free(params);
    return (0);
}

int ft_objet(char *buf, t_conf *conf)
{
    t_objet     *obj;
    double      *param;
    int         i;

    i = 0;
    obj = malloc(sizeof(t_objet));

    while (buf[i] && (buf[i] == ' ' || buf[i] == 9))
        i++;
    if (buf[i] && buf[i + 1] && buf[i] == 's' && buf[i + 1] == 'p')
    {
        obj->type = SPHERE;
        param =  get_params(buf, 7);
    }
    else if (buf[i] && buf[i + 1] && buf[i] == 'p' && buf[i + 1] == 'l')
    {
        param =  get_params(buf, 9);
         obj->type = PLANE;
    }
    else if (buf[i] && buf[i + 1] && buf[i] == 'c' && buf[i + 1] == 'y')
    {
        param =  get_params(buf, 11);
        obj->type = CYLINDER;
    }
    else
    {
        free(obj);
        return (1);
    }
	 if (param == NULL)
        return (1);

    if (( obj->type == SPHERE && ft_process_range_sphere(param) == 1) || ( obj->type == PLANE && ft_process_range_flat(param) == 1) || ( obj->type == CYLINDER && ft_process_range_cylinder(param) == 1))
    {
        free(param);
        free(obj);
        return (1);
    }
    else
    {
		ft_objetinit(param, obj);
		free(param);
    }
    ft_lstadd_front(&(conf->my_scene.obj_lst), ft_lstnew(obj));
    return (0);

}

int ft_light(char *buf, t_conf *conf)
{
    double      *param;

    param = get_params(buf, 4);
	 if (param == NULL)
        return (1);
    if ( ft_process_range_light(param) == 1)
    {
        free(param);
        return (1);
    }
	else if (conf->my_scene.light_lst.radius == 0 && conf->my_scene.light_lst.pos.x == 0 && conf->my_scene.light_lst.pos.y == 0 && conf->my_scene.light_lst.pos.z == 0)
	{
    	conf->my_scene.light_lst.pos = vec(param[0], param[1], param[2]);
    	conf->my_scene.light_lst.radius = param[3];
    	free(param);
    	return (0);
	}
	else
		return (1);

}

int ft_camera(char *buff, t_conf *conf)
{
    double *params;


    params = get_params(buff, 7);
	if (params == NULL)
		return (1);
    if (ft_process_range_camara(params) == 1)
        return (1);
	else if (conf->my_scene.cam_lst.pos.x == 0 && conf->my_scene.cam_lst.pos.y == 0 && conf->my_scene.cam_lst.pos.z == 0)
    {
		camera(buff, conf);
		////
		//
		//AQUI ME PIERDOOOOOOOOO
		//
		//
    	return (0);
	}
	else
	{
		return (2);
	}
}

t_conf  ft_process(char **buff)
{
    int i;
    int x;
    int error;
    t_conf  *conf;

    conf = malloc(sizeof(t_conf));
	conf->my_scene.light_lst.radius = 0;
	conf->my_scene.light_lst.pos.x = 0;
	conf->my_scene.light_lst.pos.y = 0;
	conf->my_scene.light_lst.pos.z = 0;
	conf->my_scene.cam_lst.pos.x = 0;
	conf->my_scene.cam_lst.pos.y = 0;
	conf->my_scene.cam_lst.pos.z = 0;
	conf->my_scene.obj_lst = malloc(sizeof(t_list));
	conf->my_scene.obj_lst->content = NULL;
	conf->my_scene.obj_lst->next = NULL;

    x = 0;
    i = 0;
    error = 0;
    while (buff[i] && error == 0)
    {
        while (buff[i][x] && (buff[i][x] == ' ' || buff[i][x] == 9))
            x++;
        if (buff[i][x] && buff[i][x] == 'A')
		{
            error = ft_ambient(buff[i], &conf->my_scene);
		}
        else if (buff[i][x] && buff[i][x] == 'C')
		{
            error = ft_camera(buff[i], conf);
		}
         else if (buff[i][x] && buff[i][x] == 'L')
		 {
            error = ft_light(buff[i], conf);
		 }
         else if (buff[i][x] && buff[i][x + 1] && ((buff[i][x] == 's' && buff[i][x + 1] == 'p') || (buff[i][x] == 'p' && buff[i][x + 1] == 'l') || (buff[i][x] == 'c' && buff[i][x + 1] == 'y')))
		 {
             error = ft_objet(buff[i], conf);
		 }
        else if (buff[i][x])
		{
			conf->flag.error = 2;
            return (*conf);
		}
        i++;
        x = 0;
    }
	if (error != 0)
		{
            conf->flag.error = error;
            return (*conf);
        }
	return (*conf);
}
