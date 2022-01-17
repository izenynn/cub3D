#include "cub3d.h"

int skip_spaces(char *line, int i)
{
	if (!line)
		return (0);
	while (line && line[i] && line[i] == ' ')
		i++;
	return (i);
}
/*
 * Aqui solo se entra en la primera linea del mapa y la ultima, quizas, en caso de encontrar un espacio, habria que
 * mirar en la siguiente o anterior linea a ver si hay un 1 cerrando el perimetro correctamente
 */
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
	//printf("LINE: %s\nindex %d\n map->lines%d\n", line,  index, (*map)->lines);
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
	//printf("%d\n", (*map)->index);
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
	//printf("IN\n");
	while ((*map)->buffer[(*map)->aux] && (*map)->buffer[(*map)->aux][0] == '\n')
		(*map)->aux++;
	(*map)->index = (*map)->aux;
	while ((*map)->aux < ((*map)->lines - 1) && (*map)->buffer[(*map)->aux])
	{
	//	printf("aux = %d\n", (*map)->aux);
		if (line_handler((*map)->buffer[(*map)->aux++], ++i, map) != 0)
			return (1);
	}
	//printf("%d\n", i);
	(*map)->map = (char **)ft_calloc(1, sizeof(char *) * (i + 3));
	//ft_bzero((void *)(*map)->map, sizeof((*map)->map));
	if (!(*map)->map)
		return (1);
	fill_map(map);
	return (0);
}

/*
 *
 * Primera linea del MAPA -> Tiene que ser todo 1; Puede tener espacios de por medio, con la ultima pasa lo mismo, aplicamos el mismo proceso.
 * comprobar que todas las lineas esten cerradas = line[0] == 1 && line[strlen(line) - 1] == 1
 *
 */