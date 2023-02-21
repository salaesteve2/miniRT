/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:45:31 by sasalama          #+#    #+#             */
/*   Updated: 2023/02/21 09:31:21 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Creación ventana
typedef struct s_s
{
	void	*mlx;
	void	*mlx_win;
}				t_s;

int	ft_exit_hook(t_s *window)
{
	mlx_destroy_window(window->mlx, window->mlx_win);
	exit(-1);
}

int	key_hook(int keycode, t_s *window)
{
	if (keycode == 53)
		ft_exit_hook(window);
	return (0);
}

void	ft_mlx_init(void)
{
	t_s		window;

	window.mlx = mlx_init();
	window.mlx_win = mlx_new_window(window.mlx, 1080, 720, "MiniRT");
	mlx_key_hook(window.mlx_win, key_hook, &window);
	mlx_hook(window.mlx_win, 17, 1L << 17, ft_exit_hook, &window);
	mlx_loop(window.mlx);
	free(window.mlx);
	free(window.mlx_win);
}
/*
Normalizar vector es transormar un vector con la misma direccion y sentido pero modulo 1
Reduce considerablemente la carga computacional

v = v / |v| (4, 2, 3) / √(4^2, 2^2, 3^2)
*/

int	main(int argc, char *argv[])
{
	char	*s;
	char	**lines;
	int		x;

	if (argc != 2)
	{
		perror("Error: Number of arguments");
		return (1);
	}
	else if (ft_strncmp_rev(argv[1], ".rt", 3))
	{
		perror("Error: Argument must be a '.rt' file");
		return (1);
	}
	s = ft_data(argv);
	if (!s)
	{
		perror("Error: In open the file");
		return (1);
	}
	lines = ft_split(s, '\n');
	x = 0;
	while (lines[x])
	{
		printf("%s\n", lines[x]);
		x++;
	}
	// Crear ventana
	ft_mlx_init();
	return (0);
}
