/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:55:03 by sasalama          #+#    #+#             */
/*   Updated: 2023/02/20 10:37:17 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_data(char *argv[])
{
	int		fd;
	char	*s;
	char	*s2;
	char	*tmp;
	char	*tmp2;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (0);
	s = get_next_line(fd, 1);
	s2 = malloc(1);
	if (!s)
		return (0);
	while (s)
	{
		tmp = s;
		tmp2 = s2;
		s2 = ft_strjoin(s2, s);
		free(tmp2);
		free(tmp);
		s = get_next_line(fd, 1);
	}
	close(fd);
	return (s2);
}
