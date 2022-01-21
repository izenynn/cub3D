/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:20:37 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/19 14:34:25 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* standard libraries */
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

/* standard unix library */
# include <unistd.h>

/* open() */
# include <fcntl.h>

/* math */
#include <math.h>

/* minilibx */
# include <mlx.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

/* our own implementation of libc */
# include <libft.h>

/* window resolution */
# ifndef WIN_W
#  define WIN_W 1280
# endif
# ifndef WIN_H
#  define WIN_H 720
# endif

/* minimap scale --> ?:1 */
# define MINIMAP_SCALE 10
/* minimap border offset % */
# define MM_OFFSET 2

/* other useful macros */
# define WALL '1'
# define Y 0
# define X 1
# define WHITE 0xFFFFFF
# define MINIMAP_FLOOR 0xFECEA8
# define MINIMAP_WALL 0x2A363B
# define MINIMAP_DOOR 0x99B898

/* minilibx keymaps */
# ifdef OSX
#  define KEY_ESC 53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_P 35
#  define KEY_MINUS 27
#  define KEY_PLUS 24
#  define KEY_R 15
#  define KEY_U 32
#  define KEY_J 38
#  define KEY_I 34
#  define KEY_K 40
#  define KEY_O 31
#  define KEY_L 37
# else
#  ifndef LINUX
#   define LINUX
#  endif
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_A 97
#  define KEY_D 100
#  define KEY_P 112
#  define KEY_MINUS 45
#  define KEY_PLUS 61
#  define KEY_R 114
#  define KEY_U 117
#  define KEY_J 106
#  define KEY_I 105
#  define KEY_K 107
#  define KEY_O 111
#  define KEY_L 108
# endif

/* s_map: map struct
 *
 * res[2]	-> resolution of the window defined on the map file
 * *NO, *SO, *WE, *EA	-> path to the different wall textures
 * *S		-> sprite texture path
 * *fRGB	-> floor rgb colors
 * *cRGB	-> ceiling rgb colors
 */
typedef struct s_map {
	char	**buffer;
	char	**map;
	int		width;
	int		height;
	int		res[2];
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	char	*frgb;
	char	*crgb;
}	t_map;

/* s_img: minilibx image struct
 *
 * *img		-> pointer to the image
 * *addr	-> pointer to the pixels data
 * bpp		-> bits per pixel
 * line_len -> len of a line of pixeles in *addr
 * endian	-> SO endian type (0 = small endian, 1 = big endian)
 */
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

/* s_p: player struct */
typedef struct s_p {
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}	t_p;

/* s_vars: program struct */
typedef struct s_vars {
	t_map	map;
	t_p		p;
	t_img	img;
	t_img	minimap;
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_ray {
	int		map_x;
	int		map_y;
	float	cam_x;
	float	cam_y;
	float	dir_x;
	float	dir_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

/* parse_map.c */
int		first_read(char *str, t_map *map);
int		check_format(char *str);

/* error_utils.c */
void	perror_exit(const char *s);
int		perror_ret(const char *s, int ret_code);
int		error_ret(const char *s, int ret_code);

/* utils.c */
void	free_split(char **split);
void	free_vars(t_vars *vars);
void	free_all(t_vars *vars);
void	reset_vars(t_vars *vars);
int		initialise_vars(t_vars *vars);

/* mlx_main.c */
int		mlx_main(t_vars *vars);

/* mlx_hook.c */
int		close_win(t_vars *vars);
int		key_hook(int keycode, t_vars *vars);

/* mlx_init.c */
void	initialise_mlx(t_vars *vars);

/* mlx_utils.c */
void	img_pixel_put(t_img img, int x, int y, int color);

/* mlx_loop.c */
int		game_loop(void *vars);

/* draw.c */
void	draw(t_vars *vars);

#endif
