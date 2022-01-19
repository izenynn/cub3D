/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:37:56 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/19 09:20:00 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//static void	fill_minimap(t_vars *vars)

static void	initialise_minimap(t_vars *vars)
{
	int	map[2];
	int	pixel[2];
	int	offset[2];

	offset[X] = 0;
	offset[Y] = 0;
	if (WIN_W > WIN_H)
		offset[Y] = WIN_W / MINIMAP_SCALE - WIN_H / MINIMAP_SCALE;
	else
		offset[X] = WIN_H / MINIMAP_SCALE - WIN_W / MINIMAP_SCALE;
	//
	vars->minimap.img = mlx_new_image(vars->mlx,
		fmax(WIN_W, WIN_H) / MINIMAP_SCALE, fmax(WIN_W, WIN_H) / MINIMAP_SCALE);
	vars->minimap.addr = mlx_get_data_addr(vars->minimap.img,
			&vars->minimap.bpp, &vars->minimap.line_len, &vars->minimap.endian);
	int y = -1;
	while (++y < fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
	{
		int x = -1;
		while (++x < fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
		{
			img_pixel_put(vars->minimap, x, y, MINIMAP_WALL);
		}
	}

	map[Y] = -1;
	while (++map[Y] < vars->map.height)
	{
		map[X] = -1;
		while (++map[X] < vars->map.width)
		{
			pixel[Y] = map[Y] * (WIN_H / MINIMAP_SCALE) / vars->map.height;
			while (pixel[Y] < (map[Y] + 1) * (WIN_H / MINIMAP_SCALE) / vars->map.height)
			{
				pixel[X] = map[X] * (WIN_W / MINIMAP_SCALE) / vars->map.width;
				while (pixel[X] < (map[X] + 1) * (WIN_W / MINIMAP_SCALE) / vars->map.width)
				{
					if (vars->map.map[map[Y]][map[X]] == '0')
						img_pixel_put(vars->minimap, pixel[X] + (offset[X] / 2), pixel[Y] + (offset[Y] / 2), MINIMAP_FLOOR);
					else
						img_pixel_put(vars->minimap, pixel[X] + (offset[X] / 2), pixel[Y] + (offset[Y] / 2), MINIMAP_WALL);
					pixel[X]++;
				}
				pixel[Y]++;
			}
		}
	}
}

void	initialise_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->img.img = mlx_new_image(vars->mlx, WIN_W, WIN_H);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&vars->img.bpp, &vars->img.line_len, &vars->img.endian);
	vars->win = mlx_new_window(vars->mlx, WIN_W, WIN_H, "cub3D");
	initialise_minimap(vars);
}
