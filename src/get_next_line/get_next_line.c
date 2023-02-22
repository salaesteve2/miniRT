/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:58:18 by salustianos       #+#    #+#             */
/*   Updated: 2023/02/17 12:51:55 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_read(int fd, char *cadena, char **cadenas2, int BUFFER_SIZE)
{
	int		s;
	char	*swap;

	if (!*cadenas2 || !ft_strchr(*cadenas2, '\n'))
	{
		s = read(fd, cadena, BUFFER_SIZE);
		while (s > 0)
		{
			cadena[s] = 0;
			if (!*cadenas2)
				*cadenas2 = ft_substr(cadena, 0, s);
			else
			{
				swap = *cadenas2;
				*cadenas2 = ft_strjoin(*cadenas2, cadena);
				free(swap);
			}
			if (ft_strchr(cadena, '\n'))
				break ;
			s = read(fd, cadena, BUFFER_SIZE);
		}
	}
	free(cadena);
}

static char	*ft_process(char **cadenas2)
{
	int		y;
	char	*tmp;
	char	*res;

	if (!*cadenas2)
		return (0);
	if (!ft_strchr(*cadenas2, '\n'))
	{
		res = ft_substr(*cadenas2, 0, ft_strlen(*cadenas2));
		free(*cadenas2);
		*cadenas2 = 0;
		if (res[0] == '\0')
		{
			free(res);
			return (0);
		}
		return (res);
	}
	y = ft_strlen(ft_strchr(*cadenas2, '\n'));
	res = ft_substr(*cadenas2, 0, ft_strlen(*cadenas2) - y + 1);
	tmp = *cadenas2;
	*cadenas2 = ft_substr(ft_strchr(*cadenas2, '\n'), 1, y - 1);
	free(tmp);
	return (res);
}

char	*get_next_line(int fd, int BUFFER_SIZE)
{
	char		*cadena;
	static char	*cadenas2;

	cadena = malloc(BUFFER_SIZE + 1);
	if (!cadena)
		return (0);
	if (fd == -1 || BUFFER_SIZE < 1 || read(fd, cadena, 0) == -1)
	{
		free(cadena);
		return (0);
	}
	ft_read(fd, cadena, &cadenas2, BUFFER_SIZE);
	return (ft_process(&cadenas2));
}
