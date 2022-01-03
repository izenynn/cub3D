#ifndef CUB3D_H
# define CUB3D_H

/* our own implementation of libc */
# include <libft.h>

/* standard libraries */
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

/* standard unix library */
# include <unistd.h>

/* open() */
# include <fcntl.h>

typedef struct s_utils
{
	char	**buffer;
	int	width;
	int	height;
	int	res[2];		// Resolution of the window defined on the map file;
	char	*NO;		////////////////////////////////////////;
	char	*SO;		//Path to the different wall textures///;
	char	*WE;		////////////////////////////////////////;
	char	*EA;		////////////////////////////////////////;
	char	*S;		// Sprite texture path;
	char	*fRGB;		// Floor rgb colours;
	char	*cRGB;		// Ceiling rgb colours;
}	t_utils;

/* parse_map.c */
int		first_read(char *str, t_utils *vars);
int		check_format(char *str);

/* error_utils.c */
void	perror_exit(const char *s);
int		perror_ret(const char *s, int ret_code);
int		error_ret(const char *s, int ret_code);

#endif
