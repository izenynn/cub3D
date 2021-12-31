#include "../inc/cub3D.h"

int ft_error(char *str, int err)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (err);
}

int main(int argc, char **argv)
{
	t_utils vars;

	if (argc != 2)
		return (ft_error("Usage: ./cub3D map.cub\n", 1));
	if (check_format(argv[1]) != 0)
		return (1);
	if (first_read(argv[1], &vars) != 0)
		return (1);
}
