#include "cub3d.h"

int	is_dptr_digit(char **s)
{
	int	i;
	int	j;

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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	process_colour(t_map **map, int i, char **sp)
{
	int	tmp[3];

	if (dptr_len(sp) != 3)
		return (1);
	if (is_dptr_digit(sp) == 1)
		return (2);
	tmp[0] = ft_atoi(sp[0]);
	tmp[1] = ft_atoi(sp[1]);
	tmp[2] = ft_atoi(sp[2]);
	if (tmp[0] < 0 || tmp[0] > 256 || tmp[1] < 0 || tmp[1] > 256
		|| tmp[2] < 0 || tmp[2] > 256)
		return (3);
	if (ft_strncmp((*map)->buffer[i], "F", 1) == 0)
		(*map)->frgb = create_trgb(255, tmp[0], tmp[1], tmp[2]);
	else
		(*map)->crgb = create_trgb(255, tmp[0], tmp[1], tmp[2]);
	return (0);
}

int	free_struct(t_map *map, int ret)
{
	free_split(map->buffer);
	free(map->we);
	free(map->so);
	free(map->no);
	free(map->ea);
	exit(ret);
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
