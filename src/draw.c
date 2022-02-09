/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:04:36 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/08 11:48:24 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_menu(t_vars *vars)
{
	int		y;
	void	*mlx;
	void	*win;

	mlx = vars->mlx;
	win = vars->win;
	y = 0;
	mlx_string_put(mlx, win, 15, y += 15, TEXT_COLOR,
		"Controls:");
	mlx_string_put(mlx, win, 15, y += 25, TEXT_COLOR,
		"[ W ] [ A ] [ S ] [ D ] move");
	mlx_string_put(mlx, win, 15, y += 25, TEXT_COLOR,
		"[ Shift ] sprint");
	mlx_string_put(mlx, win, 15, y += 25, TEXT_COLOR,
		"[ Mouse ] / [ Arrows ] rotate camera");
	mlx_string_put(mlx, win, 15, y += 25, TEXT_COLOR,
		"[ C ] toggle mouse");
	mlx_string_put(mlx, win, 15, y += 25, TEXT_COLOR,
		"[ E ] open / close doors");
}

void	draw_square(t_img *img, int coords[2], float side_len, int color)
{
	float	x1;
	float	y1;

	y1 = -1;
	while (++y1 < side_len)
	{
		x1 = -1;
		while (++x1 < side_len)
			img_pixel_put(img, coords[X] + x1, coords[Y] + y1, color);
	}
}

/* draw minimap on upper right corner */
static void	draw_minimap(t_vars *vars)
{
	int	side_len;
	int	screen_pos[2];
	int	it[2];

	it[Y] = -1;
	while (++it[Y] < fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
	{
		it[X] = -1;
		while (++it[X] < fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
			img_pixel_put(&vars->mm_player, it[X], it[Y],
				get_pixel_color(&vars->minimap, it[X], it[Y]));
	}
	screen_pos[X] = (vars->mm_offset[X] / 2) + (vars->p.pos_x
			* ((vars->minimap.line_len / vars->minimap.bpp * 8)
				/ fmax(vars->map->width, vars->map->height)));
	screen_pos[Y] = (vars->mm_offset[Y] / 2) + (vars->p.pos_y
			* ((vars->minimap.line_len / vars->minimap.bpp * 8)
				/ fmax(vars->map->width, vars->map->height)));
	side_len = 5;
	screen_pos[X] -= side_len / 2;
	screen_pos[Y] -= side_len / 2;
	draw_square(&vars->mm_player, screen_pos, side_len, MINIMAP_PLAYER);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->mm_player.img,
		WIN_W - (vars->mm_player.line_len / vars->mm_player.bpp * 8) - 15, 15);
}

/* draw crosshair on screen center */
static void	draw_crosshair(t_vars *vars)
{
	int	side_len;
	int	coords[2];

	side_len = 10;
	coords[X] = WIN_W / 2 - side_len / 2;
	coords[Y] = WIN_H / 2 - side_len / 2;
	draw_square(&vars->img, coords, side_len, CROSSHAIR_COLOR);
}

/* draw all on screen */
void	draw(t_vars *vars)
{
	vars->door_hit[X] = -1;
	vars->door_hit[Y] = -1;
	ft_bzero(vars->img.addr, WIN_H * WIN_W * (vars->img.bpp / 8));
	raycast_wall(vars);
	raycast_sprite(vars);
	draw_crosshair(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	draw_minimap(vars);
	draw_menu(vars);
}
