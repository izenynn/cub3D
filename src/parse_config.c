/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:03:17 by acostal-          #+#    #+#             */
/*   Updated: 2022/02/10 17:13:31 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_colour(t_map **map, int i)
{
	char	*aux;
	char	**split;

	if (ft_strncmp((*map)->buffer[i], "DOOR", 4) == 0)
	{
		if ((*map)->door)
			return (error_ret("Error\nDuplicated texture\n", 1));
		aux = ft_substr((*map)->buffer[i], 5, ft_strlen((*map)->buffer[i]));
		(*map)->door = aux;
		return (0);
	}
	else if (ft_strncmp((*map)->buffer[i], "F", 1) == 0
		|| ft_strncmp((*map)->buffer[i], "C", 1) == 0)
	{
		aux = ft_substr((*map)->buffer[i], 2, ft_strlen((*map)->buffer[i]) - 1);
		split = ft_split(aux, ',');
		free(aux);
		if (process_colour(map, i, split) == 1)
			return (error_ret("Error\nInvalid Colour\n", 1));
	}
	else
		return (1);
	if (split)
		free_split(split);
	return (0);
}

int	read_texture2(t_map **map, int i)
{
	char	*aux;

	if (ft_strncmp((*map)->buffer[i], "WE", 2) == 0)
	{
		if ((*map)->we)
			return (error_ret("Error\nDuplicated texture2\n", 1));
		aux = ft_substr((*map)->buffer[i], 3, ft_strlen((*map)->buffer[i]));
		(*map)->we = aux;
		return (0);
	}
	else if (ft_strncmp((*map)->buffer[i], "EA", 2) == 0)
	{
		if ((*map)->ea)
			return (error_ret("Error\nDuplicated texture1\n", 1));
		aux = ft_substr((*map)->buffer[i], 3, ft_strlen((*map)->buffer[i]));
		(*map)->ea = aux;
		return (0);
	}
	return (1);
}

int	read_texture(t_map **map, int i)
{
	char	*aux;

	if (ft_strncmp((*map)->buffer[i], "NO", 2) == 0)
	{
		if ((*map)->no)
			return (error_ret("Error\nDuplicated texture3\n", 1));
		aux = ft_substr((*map)->buffer[i], 3, ft_strlen((*map)->buffer[i]));
		(*map)->no = aux;
	}
	else if (ft_strncmp((*map)->buffer[i], "SO", 2) == 0)
	{
		if ((*map)->so)
			return (error_ret("Error\nDuplicated texture4\n", 1));
		aux = ft_substr((*map)->buffer[i], 3, ft_strlen((*map)->buffer[i]));
		(*map)->so = aux;
	}
	else if (read_texture2(map, i) == 0)
		return (0);
	else if (read_colour(map, i) == 1)
		return (1);
	return (0);
}

int	fill_sprites(t_map *map, int i)
{
	if (ft_strncmp(map->buffer[i], BS, ft_strlen(BS)) == 0)
	{
		map->sprite_index = i++;
		while (map->buffer[i] != NULL
			&& ft_strncmp(map->buffer[i], ES, ft_strlen(ES)) != 0)
		{
			map->sprite_cnt++;
			i++;
		}
		return (i);
	}
	else if (ft_strncmp(map->buffer[i], BP, ft_strlen(BP)) == 0)
	{
		map->pos_index = i++;
		while (map->buffer[i] != NULL
			&& ft_strncmp(map->buffer[i], EP, ft_strlen(EP)) != 0)
		{
			map->pos_cnt++;
			i++;
		}
		return (i);
	}
	return (-1);
}

int	parse_textures(t_map *map)
{
	int	i;
	int	ret;

	i = -1;
	while (map->buffer[++i] && check_if_filled(map))
	{
		ret = 0;
		tex_filler(map, &i, ret);
	}
	if (!map->no || !map->so
		|| !map->we || !map->ea || !map->frgb || !map->crgb)
		return (error_ret("Error\nMissing data on the config file",
				1));
	if (open_texture(map) == 1)
		return (-1);
	map->aux = i;
	return (i);
}
