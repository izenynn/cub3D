#include "cub3d.h"

/*
 * TODO: Si encuentro un espacio (' ') por ejemplo en la linea 7 posicion 4, vuelvo a la linea 6 y compruebo que en la posicion 3, 4 y 5 haya 1 o espacios.
 */

int skip_spaces(char *line, int i)
{
	if (!line)
		return (0);
	while (line && line[i] && line[i] == ' ')
		i++;
	return (i);
}

int check_top_and_bot(char *line)
{
	int i;

	i = -1;
	while (line[++i] && (line[i] != '\n' && line[i] != '\0'))
	{
		if (line[i] != '1' && line[i] != ' ')
			return (error_ret("Error\nFirst or last line is not filled by 1's\n", 1));
	}
	return (0);
}

int	counter(char c, t_map **map)
{
	if (c == 'E' || c == 'S' || c == 'W' || c == 'N')
		(*map)->count++;
	if ((*map)->count > 1)
		return (1);
	return (0);
}

int line_handler(char *line, int index, t_map **map)
{
	int i;

	i = skip_spaces(line, 0);
	if (index == 0 || index == (*map)->lines)
		return (check_top_and_bot(line));
	else if (line && (line[i] != '1' || line[ft_strlen(line) - 2] != '1'))
		return (error_ret("Error\nMap not closed by 1's\n", 1));
	while (line[++i] != '\n' && line[i] != '\0')
	{
		if (!(line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == ' '
			  || line[i] == 'E' || line[i] == 'W' || line[i] == 'S'))
			return (error_ret("Error\nInvalid character on the map\n", 1));
		else
		{
			if (counter(line[i], map) != 0)
				return (error_ret("Error\nToo many player spawns\n", 1));
		}
	}
	return (0);
}

void fill_map(t_map **map)
{
	int i;

	i = 0;
	while((*map)->index < ((*map)->lines) && (*map)->buffer[(*map)->index])
	{
		(*map)->map[i++] = ft_substr((*map)->buffer[(*map)->index], 0, ft_strlen((*map)->buffer[(*map)->index]) - 2);
		(*map)->index++;
	}
	i = 0;
	while((*map)->map[i])
		printf("%s\n", (*map)->map[i++]);
}

int parse_map(t_map **map)
{
	int i;

	i = -1;
	while ((*map)->buffer[(*map)->aux] && (*map)->buffer[(*map)->aux][0] == '\n')
		(*map)->aux++;
	(*map)->index = (*map)->aux;
	while ((*map)->aux < ((*map)->lines - 1) && (*map)->buffer[(*map)->aux])
	{
		if (line_handler((*map)->buffer[(*map)->aux++], ++i, map) != 0)
			return (1);
	}
	(*map)->map = (char **)ft_calloc(1, sizeof(char *) * (i + 3));
	if (!(*map)->map)
		return (1);
	fill_map(map);
	return (0);
}
