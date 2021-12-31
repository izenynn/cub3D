#ifndef CUB3D_H
#include <stdio.h>
#include <fcntl.h>
#include "../libft/inc/libft.h"
typedef struct s_utils
{
	char	**buffer;
	int	width;
	int	height;
}t_utils;
int first_read(char *str, t_utils *vars);
int ft_error(char *str, int err);
int check_format(char *str);
#endif
