/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_camera.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:44:32 by sasalama          #+#    #+#             */
/*   Updated: 2023/03/13 12:14:45 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/geometry.h"

void	camera(char *buf, t_conf *conf)
{
	double	*param;

	param = get_params(buf, 7);
	conf->my_scene.cam_lst.pos = vec(param[0], param[1], param[2]);
	conf->my_scene.cam_lst.view = vec(param[3], param[4], param[5]);
	conf->my_scene.cam_lst.grades = param[6];
}
