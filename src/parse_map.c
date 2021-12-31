#include "../inc/cub3D.h"
static int fill_buffer(char *map, int lines, t_utils *vars)
{
	int fd;
	int i;

	i = -1;
	vars->buffer = malloc(sizeof(char *) * (lines + 1));
	if (!vars->buffer)
		return (1);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (1);
	while (++i < lines)
		vars->buffer[i] = ft_get_next_line(fd);
	return (0);
}

int first_read(char *str, t_utils *vars)
{
	char *aux;
	int fd;
	int lines;

	lines = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (ft_error("Error: Opening the map file\n", 1));
	aux = ft_get_next_line(fd);
	while (aux)
	{
		++lines;
		free(aux);
		aux = ft_get_next_line(fd);
	}
	close(fd);
	if (lines == 0)
		return (ft_error("Error: Empty map\n", 1));
	if (fill_buffer(str, lines, vars) != 0)
		return (ft_error("Error: Fatal\n", 1));
	return (0);
}

int check_format(char *str)
{
	char *tmp;

	tmp = ft_strdup(str);
	ft_strrev(tmp);
	if (ft_strncmp(tmp, "buc.", 4) != 0)
	{	
		free(tmp);
		return (ft_error("Invalid map format\n", 1));
	}
	free(tmp);
	return (0);
}
