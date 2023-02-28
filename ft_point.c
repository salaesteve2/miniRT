int ft_escalar_prod(t_vect a, t_vect b)
{
	int res;

	res = a.x * b.x + a.y *b.y + a.z + b.z;
	return (res);
}

int ft_module(t_vect v)
{
    int res;

    res = v.x * v.x + v.y * v.y + v.z * v.z;
    res = sqrt(res);
    return (res);

}

int ft_distance_origin(int x, int y, int z)
{
	int res;

	res = x * x + y * y + z * z;
	res = sqrt(res);
	return (res);
}


void	ft_point (int x, int y, int z, t_objet obj, t_conf *conf)
{
	if (obj->type == 1)
	{
		t_sphere *aux = (t_sphere *)obj->objet;
		///la normal(vector perpendicular) al punto, se usará para la luz
		t_vector perp = vec(x - aux->center->x, y - aux->center->y, z - aux->center->z);
		//el vector del origen/camara al punto, necesario para el tamaño y ubicacion del pixel
		t_vector origpoint = vec(x, y, z);
				///producto escalar de vect al obj y eje de pantalla / distancia = seno del angulo de visión.
				/////heidht
		int pe = ft_escalar_prod(conf->my_camera.h, origpoint);

		int pe2 = ft_escalar_prod(conf->my_camera.w, origpoint);


		int sen = pe / (ft_module(origpoint));

		int sen2 = pe2 / (ft_module(origpoint));


		int coordz = (sen / sin(conf->my_camera.radian)) * 1080;

		if (coordz > 360 || coordz < -360)
			break;

		int coordy = (sen2 / sin(conf->my_camera.radian)) * 1080;

		if (coordy > 540 || coordy < -540)
            break;
		else
		{
			///put point at coordz coordy of the screen//

			////NO TENEMOS EN CUENTA LA INTERSECCION DE OTROS OBJETOS SOBRE EL VECTOR DE LA LUZ FOCAL; vamos que no hay sombra
			int intensity = ft_escalar_prod(vect(x - conf->my_scene.light_lst.pos.x, y - conf->my_scene.light_lst.pos.y, z - conf->my_scene.light_lst.pos.z), perp);

			unsigned char red = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.r / 255) * aux->color.r * intensity;
			unsigned char green = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.g / 255) * aux->color.g * intensity;
			unsigned char blue = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.b / 255) * aux->color.b * intensity;

			/// FALTAAA: pintamos pixel con colores red, blue y green en coordy, coordz de la pantalla...



		}
		else if (obj->type == 2)
		{

			////para circulo/base


			//
			//para borde/columna
			//if (
		}
		else if (obj->type == 3)
        {
			 t_m_plane *aux = (t_m_plane *)obj->objet;
        //el vector del origen/camara al punto, necesario para el tamaño y ubicacion del pixel
        t_vector origpoint = vec(x, y, z);
                ///producto escalar de vect al obj y eje de pantalla / distancia = seno del angulo de visión.
                /////heidht
        int pe = ft_escalar_prod(conf->my_camera.h, origpoint);

        int pe2 = ft_escalar_prod(conf->my_camera.w, origpoint);


        int sen = pe / (ft_module(origpoint));

        int sen2 = pe2 / (ft_module(origpoint));


        int coordz = (sen / sin(conf->my_camera.radian)) * 1080;

        if (coordz > 360 || coordz < -360)
            break;

        int coordy = (sen2 / sin(conf->my_camera.radian)) * 1080;

		 if (coordy > 540 || coordy < -540)
            break;
        else
        {
            ///put point at coordz coordy of the screen//

            ////NO TENEMOS EN CUENTA LA INTERSECCION DE OTROS OBJETOS SOBRE EL VECTOR DE LA LUZ FOCAL; vamos que no hay sombras aún
            int intensity = ft_escalar_prod(vect(x - conf->my_scene.light_lst.pos.x, y - conf->my_scene.light_lst.pos.y, z - conf->my_scene.light_lst.pos.z), aux->normal);

            unsigned char red = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.r / 255) * aux->color.r * intensity;
            unsigned char green = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.g / 255) * aux->color.g * intensity;
            unsigned char blue = (conf->my_scene.ambient.radius * conf->my_scene.ambient.color.b / 255) * aux->color.b * intensity;

            /// FALTAAA: pintamos pixel con colores red, blue y green en coordy, coordz de la pantalla...


        }




	}	

}
