/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:16:26 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/09 12:23:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	first_read(t_map *map, char *str)
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
	return (0);
}

int	parse_sprites(t_map *map)
{
	char	**aux;
	int		i;
	int		id;

	alloc_sprites_struct(map);
	if (!map->sprites || !map->spaux)
		return (-1);
	i = map->sprite_index + 1;
	id = 0;
	while (map->buffer[i])
	{
		if (ft_strncmp(map->buffer[i], ES, ft_strlen(ES)) == 0)
			break ;
		aux = ft_split(map->buffer[i], ' ');
		if (aux[1])
		{
			map->sprites[id] = ft_split(aux[1], ';');
			if (dptr_len(map->sprites[id]) != 6)
				return (error_ret("Error\nAnimations need 6 textures\n", -1));
		}
		else
			return (-1);
		store_sprites(map, aux, &i, &id);
	}
	return (0);
}

int	save_pos(t_map *map, int i, int j, int *cnt)
{
	char	*aux;
	char	**aux2;

	if (ft_strncmp(map->buffer[i], map->spaux[j].type,
			ft_strlen(map->spaux[j].type)) == 0)
	{
		aux = ft_substr(map->buffer[i], ft_strlen(map->spaux[j].type) + 1,
				ft_strlen(map->buffer[i]));
		aux2 = ft_split(aux, ',');
		map->sprite[*cnt].x = ft_atoi(aux2[0]);
		map->sprite[*cnt].y = ft_atoi(aux2[1]);
		map->sprite[*cnt++].id = map->spaux[j].id;
		free_split(aux2);
		free(aux);
		return (1);
	}
	return (0);
}

int	store_pos(t_map *map)
{
	int		cnt;
	int		i;
	int		j;

	map->sprite = (t_sprite *)ft_calloc(map->pos_cnt + 2, sizeof(t_sprite));
	if (!map->sprite)
		return (-1);
	cnt = 0;
	i = map->pos_index + 1;
	while (map->buffer[i])
	{
		j = -1;
		while (++j < map->sprite_cnt)
			if (save_pos(map, i, j, &cnt) == 1)
				break ;
		i++;
	}
	return (0);
}

int	init_parser(t_map *map, char *str)
{
	if (map->lines == 0)
		return (error_ret("Error\nempty map\n", 1));
	if (fill_buffer(str, map->lines, map) < 0)
		return (error_ret("Error\nfatal error\n", 1));
	if (parse_textures(map) < 0)
		return (1);
	if (parse_sprites(map) == -1 || store_pos(map))
		return (1);
	if (parse_map(&map) != 0)
		return (free_struct(map, 1));
	if (last_map_check(&map) != 0)
		return (free_struct(map, 1));
	if (map->p_pos[0] == -1 || map->p_pos[1] == -1)
		free_struct(map, 1);
	return (0);
}
