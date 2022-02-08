/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:48:24 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/08 12:48:26 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map	*map)
{
	map->buffer = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->door = NULL;
	map->height = 0;
	map->width = 0;
	map->crgb = 0;
	map->frgb = 0;
	map->lines = 0;
	map->count = 0;
	map->sprite_cnt = 0;
	map->pos_cnt = 0;
	map->p_pos[0] = -1;
	map->p_pos[1] = -1;
	map->pos_index = -1;
	map->sprite_index = -1;
}

int	dptr_len(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	skip_spaces(char *line, int i)
{
	if (!line)
		return (0);
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	counter(char c, t_map **map)
{
	if (c == 'E' || c == 'S' || c == 'W' || c == 'N')
		(*map)->count++;
	if ((*map)->count > 1)
		return (1);
	return (0);
}
