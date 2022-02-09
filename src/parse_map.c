/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:03:39 by acostal-          #+#    #+#             */
/*   Updated: 2022/02/09 13:03:40 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_top_and_bot(const char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (error_ret("Error\nFirst or last"
					"line is not filled by 1's\n", 1));
	}
	return (0);
}

static int	line_handler(char *line, int index, t_map **map)
{
	int	i;

	i = skip_spaces(line, 0);
	if (index == 0 || index == (*map)->lines)
		return (check_top_and_bot(line));
	else if (*line && (line[i] != '1' || line[ft_strlen(line) - 1] != '1'))
		return (error_ret("Error\nMap not closed by 1's\n", 1));
	while (*line && line[++i] != '\n' && line[i] != '\0')
	{
		if (!(line[i] == '0' || line[i] == '1' || line[i] == 'N'
				|| line[i] == ' ' || line[i] == 'E'
				|| line[i] == 'W' || line[i] == 'S'
				|| line[i] == 'C' || line[i] == 'O'))
			return (error_ret("Error\nInvalid character on the map\n", 1));
		else
		{
			if (counter(line[i], map) != 0)
				return (error_ret("Error\nToo many player spawns\n", 1));
		}
	}
	return (0);
}

int	parse_map(t_map **map)
{
	int	i;

	i = -1;
	while ((*map)->buffer[(*map)->aux]
		&& (*map)->buffer[(*map)->aux][0] == '\0')
		(*map)->aux++;
	(*map)->index = (*map)->aux;
	while ((*map)->aux <= ((*map)->lines) && (*map)->buffer[(*map)->aux])
	{
		if (line_handler((*map)->buffer[(*map)->aux], ++i, map) != 0)
			return (1);
		if ((int)ft_strlen((*map)->buffer[(*map)->aux]) > (*map)->width)
			(*map)->width = (int)ft_strlen((*map)->buffer[(*map)->aux]);
		(*map)->aux++;
	}
	(*map)->map = (char **)ft_calloc((i + 2), sizeof(char *));
	if (!(*map)->map)
		return (1);
	(*map)->height = i + 1;
	fill_map(map);
	return (0);
}
