/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:16:26 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/01 13:58:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	fill_buffer(char *file, int lines, t_map *map)
{
	char	*s;
	int		fd;
	int		i;

	i = -1;
	map->buffer = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!map->buffer)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	while (++i < lines)
	{
		s = ft_get_next_line(fd);
		map->buffer[i] = ft_substr(s, 0, ft_strlen(s) - 1);
		free(s);
	}
	map->buffer[i] = NULL;
	close(fd);
	return (0);
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
	return (0);
}
int parse_sprites(t_map *map)
{
	char	**aux;
	int		i;
	int		id;

	map->sprites = (char ***)ft_calloc(map->sprite_cnt + 1, sizeof(char **));
	map->spaux = (t_spaux *)ft_calloc(map->sprite_cnt + 1, sizeof(t_spaux));
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
			map->sprites[id] = ft_split(aux[1], ';');
		else
			return (-1);
		map->spaux[id].id = id;
		map->spaux[id].type = ft_strdup(aux[0]);
		id++;
		i++;
		free_split(aux);
	}
	return (0);
}

int store_pos(t_map *map)
{
	char *aux;
	char **aux2;
	int cnt;
	int i;
	int j;

	map->sprite = (t_sprite *)ft_calloc(map->pos_cnt + 2, sizeof(t_sprite));
	if (!map->sprite)
		return (-1);
	cnt = 0;
	i = map->pos_index + 1;
	while (map->buffer[i])
	{
		j = -1;
		//printf("[paco-> %s]\n", map->buffer[i]);
		while (++j < map->sprite_cnt)
		{
			if (ft_strncmp(map->buffer[i], map->spaux[j].type, ft_strlen(map->spaux[j].type)) == 0)
			{
				aux = ft_substr(map->buffer[i], ft_strlen(map->spaux[j].type) + 1, ft_strlen(map->buffer[i]));
				aux2 = ft_split(aux, ',');
				//printf("%s %s\n", aux2[0], aux2[1]);
				map->sprite[cnt].x = ft_atoi(aux2[0]);
				map->sprite[cnt].y = ft_atoi(aux2[1]);
				map->sprite[cnt++].id = map->spaux[j].id;
				free_split(aux2);
				free(aux);
				break ;
			}
		}
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
		return (error_ret("Error\nInvalid texture file\n", 1));
	if (parse_sprites(map) == -1 || store_pos(map))
		return (error_ret("Error\nFATAL -> MALLOC FAILED\n", 1));
	if (parse_map(&map) != 0)
		return (free_struct(map, 1));
	if (last_map_check(&map) != 0)
		return (free_struct(map, 1));
	//printf("%s\n%s\n%s\n%s\n\n\n", map->no, map->so, map->we, map->ea);
	//printf("%s\n%s\n", map->sprites[0][0], map->sprites[0][1]);
	//printf("%s\n%s\n", map->sprites[1][0], map->sprites[1][1]);
	//printf("x %d y%d id %d  \n", map->sprite[1].x, map->sprite[1].y, map->sprite[1].id);
	if (map->p_pos[0] == -1 || map->p_pos[1] == -1)
		free_struct(map, 1);
	return (0);
}
