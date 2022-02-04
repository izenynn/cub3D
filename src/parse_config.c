#include "cub3d.h"

static int	read_colour(t_map **map, int i)
{
	char	*aux;
	char	**split;

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

static int	read_texture(t_map **map, int i)
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

static int	open_texture(t_map *map)
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
	while (map->buffer[++i] && (!map->no || !map->so || !map->we
			|| !map->ea || !map->frgb || !map->crgb))
	{
		if (ft_strlen(map->buffer[i]) == 0)
			continue ;
		else if (read_texture(&map, i) == 1)
			return (-1);
	}
	if (!map->no || !map->so
		|| !map->we || !map->ea || !map->frgb || !map->crgb)
		return (error_ret("Error\nMissing data on the config file",
				-1));
	if (open_texture(map) == 1)
		return (-1);
	map->aux = i;
	return (i);
}
