/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:16:26 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/10 15:31:07 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int fill_buffer(char *file, int lines, t_map *map)
{
	int fd;
	int i;

	i = -1;
	map->buffer = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!map->buffer)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	while (++i < lines)
		map->buffer[i] = ft_get_next_line(fd);
	return (0);
}

int first_read(char *str, t_map *map)
{
	char *aux;
	int fd;
	int lines;

	lines = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (perror_ret(str, 1));
	aux = ft_get_next_line(fd);
	while (aux)
	{
		++lines;
		free(aux);
		aux = ft_get_next_line(fd);
	}
	close(fd);
	if (lines == 0)
		return (error_ret("Error: empty map\n", 1));
	if (fill_buffer(str, lines, map) != 0)
		return (error_ret("Error: fatal error\n", 1));
	return (0);
}

int check_format(char *str)
{
	char *tmp;

	tmp = ft_strdup(str);
	ft_strrev(tmp);
	if (ft_strncmp(tmp, "buc.", 4) != 0)
	{	
		free(tmp);
		return (error_ret("Error: invalid map format\n", 1));
	}
	free(tmp);
	return (0);
}
