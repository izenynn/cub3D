/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:21:54 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/08 14:22:00 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	minimap_pixel_put(t_vars *vars, int pixel[2], int color)
{
	img_pixel_put(
		&vars->minimap,
		pixel[X] + (vars->mm_offset[X] / 2),
		pixel[Y] + (vars->mm_offset[Y] / 2),
		color);
}

static int	get_square_color(t_vars *vars, int map[2])
{
	if (vars->map->map[map[Y]][map[X]] == FLOOR)
		return (MINIMAP_FLOOR);
	else if (vars->map->map[map[Y]][map[X]] == DOOR_CLOSE
		|| vars->map->map[map[Y]][map[X]] == DOOR_OPEN)
		return (MINIMAP_DOOR);
	else
		return (MINIMAP_WALL);
}

static void	draw_minimap_square(t_vars *vars, int map[2])
{
	int	pixel[2];
	int	draw_end_y;
	int	draw_end_x;
	int	color;

	draw_end_y = (map[Y] + 1) * (fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
		/ fmax(vars->map->width, vars->map->height);
	pixel[Y] = map[Y] * (fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
		/ fmax(vars->map->width, vars->map->height);
	while (pixel[Y] < draw_end_y)
	{
		draw_end_x = (map[X] + 1) * (fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
			/ fmax(vars->map->width, vars->map->height);
		pixel[X] = map[X] * (fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
			/ fmax(vars->map->width, vars->map->height);
		while (pixel[X] < draw_end_x)
		{
			color = get_square_color(vars, map);
			minimap_pixel_put(vars, pixel, color);
			pixel[X]++;
		}
		pixel[Y]++;
	}
}

static void	draw_minimap(t_vars *vars)
{
	int	map[2];

	map[Y] = -1;
	while (++map[Y] < vars->map->height)
	{
		if (vars->map->map[map[Y]] == NULL)
			break ;
		map[X] = -1;
		while (++map[X] < vars->map->width)
		{
			if (vars->map->map[map[Y]][map[X]] == '\0')
				break ;
			draw_minimap_square(vars, map);
		}
	}
}

void	initialise_minimap(t_vars *vars)
{
	calculate_inner_map_offset(vars);
	init_mlx_image(vars);
	draw_background(vars);
	draw_minimap(vars);
}
