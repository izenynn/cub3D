/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:16:26 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/14 11:34:44 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	fill_buffer(char *file, int lines, t_map *map)
{
	int	fd;
	int	i;

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

int	read_texture(t_map **map, int i)
{
	char	*aux;

	if (ft_strncmp((*map)->buffer[i], "NO", 2) == 0)
	{
		aux = ft_substr((*map)->buffer[i], 3, ft_strlen((*map)->buffer[i]));
		(*map)->no = aux;
	}
	else if (ft_strncmp((*map)->buffer[i], "SO", 2) == 0)
	{
		aux = ft_substr((*map)->buffer[i], 3, ft_strlen((*map)->buffer[i]));
		(*map)->so = aux;
	}
	else if (ft_strncmp((*map)->buffer[i], "WE", 2) == 0)
	{
		aux = ft_substr((*map)->buffer[i], 3, ft_strlen((*map)->buffer[i]));
		(*map)->we = aux;
	}
	else if (ft_strncmp((*map)->buffer[i], "EA", 2) == 0)
	{
		aux = ft_substr((*map)->buffer[i], 3, ft_strlen((*map)->buffer[i]));
		(*map)->ea = aux;
	}
	else
		return (1);
	return (0);
}

int	open_texture(t_map *map)
{
	int	fd[4];

	fd[0] = open(map->no, O_RDONLY);
	fd[1] = open(map->so, O_RDONLY);
	fd[2] = open(map->we, O_RDONLY);
	fd[3] = open(map->ea, O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1 || fd[3] == -1)
		return (1);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	return (0);
}

int	parse_textures(t_map *map)
{
	int	i;

	i = -1;
	while (map->buffer[++i] && (!map->no || !map->so || !map->we || !map->ea))
	{
		if (read_texture(&map, i) == 1)
			return (1);
	}
	if (open_texture(map) == 1)
		return (error_ret("Error\nInvalid texture file\n", 1));
	return (0);
}

int	first_read(char *str, t_map *map)
{
	char	*aux;
	int		fd;
	int		lines;

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
		return (error_ret("Error\n empty map\n", 1));
	if (fill_buffer(str, lines, map) != 0)
		return (error_ret("Error\n fatal error\n", 1));
	if (parse_textures(map) != 0)
		return (error_ret(NULL, 1));
	return (0);
}

int	check_format(char *str)
{
	char	*tmp;

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
