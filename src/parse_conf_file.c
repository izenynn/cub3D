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
	map->buffer[i] = NULL;
	close(fd);
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int dptr_len(char **s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int is_dptr_digit(char **s)
{
	int i;
	int j;

	i = -1;
	while (s[++i])
	{
		j = -1;
		while (s[i][++j] != '\n' && s[i][j])
			if (ft_isdigit(s[i][j]) == 0)
				return (1);
	}
	return (0);
}

int process_colour(t_map **map, int i, char **sp)
{
	int tmp[3];

	if (dptr_len(sp) != 3)
		return (1);
	if (is_dptr_digit(sp) == 1)
		return (2);
	tmp[0] = ft_atoi(sp[0]);
	tmp[1] = ft_atoi(sp[1]);
	tmp[2] = ft_atoi(sp[2]);
	if (tmp[0] < 0 || tmp[0] > 256 || tmp[1] < 0 || tmp[1] > 256 || tmp[2] < 0 || tmp[2] > 256)
		return (3);
	if (ft_strncmp((*map)->buffer[i], "F", 1) == 0)
		(*map)->frgb = create_trgb(255, tmp[0], tmp[1], tmp[2]);
	else
		(*map)->crgb = create_trgb(255, tmp[0], tmp[1], tmp[2]);
	return (0);
}

int read_colour(t_map **map, int i)
{
	char *aux;
	char **split;

	if (ft_strncmp((*map)->buffer[i], "F", 1) == 0 || ft_strncmp((*map)->buffer[i], "C", 1) == 0)
	{
		aux = ft_substr((*map)->buffer[i], 2, ft_strlen((*map)->buffer[i]) - 1);
		split = ft_split(aux, ',');
		free(aux);
		if (process_colour(map, i, split) == 1)
			return (1);
	}
	else
		return (1);
	if (split)
		free_split(split);
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
	else if (read_colour(map, i) == 1)
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
	while (map->buffer[++i] && (!map->no || !map->so || !map->we || !map->ea || !map->frgb || !map->crgb))
	{
		if (map->buffer[i][0] == '\n')
			continue ;
		else if (read_texture(&map, i) == 1)
			return (-1);
	}
	//if (open_texture(map) == 1) /*  UNCOMMENT THIS AS SOON AS WE START WORKING WITH VALID TEXTURE FILES  */
	//	return (-1);
	map->aux = i;
	return (i);
}

int free_struct(t_map *map, int ret)
{
	free_split(map->buffer);
	free(map->we);
	free(map->so);
	free(map->no);
	free(map->ea);
	exit(ret);
}

int	first_read(char *str, t_map *map)
{
	char	*aux;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (perror_ret(str, 1));
	aux = ft_get_next_line(fd);
	while (aux)
	{
		++map->lines;
		free(aux);
		aux = ft_get_next_line(fd);
	}
	close(fd);
	if (map->lines == 0)
		return (error_ret("Error\n empty map\n", 1));
	if (fill_buffer(str, map->lines, map) < 0)
		return (error_ret("Error\n fatal error\n", 1));
	if (parse_textures(map) < 0)
		return (error_ret("Error\nInvalid texture file\n", 1));
	if (parse_map(&map) != 0)
		return (free_struct(map, 1));
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
		return (error_ret("Error\ninvalid map format\n", 1));
	}
	free(tmp);
	return (0);
}
