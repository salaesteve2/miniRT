/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:45:50 by sasalama          #+#    #+#             */
/*   Updated: 2023/02/20 09:41:32 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include "mlx/mlx.h"
# include "libft/libft.h"

char	*ft_data(char *argv[]);
int		ft_process_range_ambient_light(double *nb);
int		ft_process_range_camara(double *nb);
int		ft_process_range_light(double *nb);
int		ft_process_range_sphere(double *nb);
int		ft_process_range_flat(double *nb);
int		ft_process_range_cylinder(double *nb);

#endif