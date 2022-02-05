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

	vars->mm_offset[X] = 0;
	vars->mm_offset[Y] = 0;
	/*if (WIN_W > WIN_H)
		vars->mm_offset[Y] = WIN_W / MINIMAP_SCALE - WIN_H / MINIMAP_SCALE;
	else if (WIN_H > WIN_W)
		vars->mm_offset[X] = WIN_H / MINIMAP_SCALE - WIN_W / MINIMAP_SCALE;*/
	//
	if (vars->map.width > vars->map.height)
		vars->mm_offset[Y] = (vars->map.width - vars->map.height)
			* (fmax(WIN_W, WIN_H) / MINIMAP_SCALE / vars->map.width);
	else if (vars->map.height > vars->map.width)
		vars->mm_offset[X] = (vars->map.height - vars->map.width)
			* (fmax(WIN_W, WIN_H) / MINIMAP_SCALE / vars->map.height);

	// images
	vars->minimap.img = mlx_new_image(vars->mlx,
		fmax(WIN_W, WIN_H) / MINIMAP_SCALE, fmax(WIN_W, WIN_H) / MINIMAP_SCALE);
	vars->minimap.addr = mlx_get_data_addr(vars->minimap.img,
			&vars->minimap.bpp, &vars->minimap.line_len, &vars->minimap.endian);

	vars->mm_player.img = mlx_new_image(vars->mlx,
		fmax(WIN_W, WIN_H) / MINIMAP_SCALE, fmax(WIN_W, WIN_H) / MINIMAP_SCALE);
	vars->mm_player.addr = mlx_get_data_addr(vars->mm_player.img,
			&vars->mm_player.bpp, &vars->mm_player.line_len, &vars->mm_player.endian);

	// draw minimap back grund
	int y = -1;
	while (++y < fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
	{
		int x = -1;
		while (++x < fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
			img_pixel_put(&vars->minimap, x, y, MINIMAP_WALL);
	}

	map[Y] = -1;
	while (++map[Y] < vars->map.height)
	{
		if (vars->map.map[map[Y]] == NULL)
			break ;
		map[X] = -1;
		while (++map[X] < vars->map.width)
		{
			if (vars->map.map[map[Y]][map[X]] == '\0')
				break ;
			pixel[Y] = map[Y] * (fmax(WIN_W, WIN_H) / MINIMAP_SCALE) / fmax(vars->map.width, vars->map.height);
			while (pixel[Y] < (map[Y] + 1) * (fmax(WIN_W, WIN_H) / MINIMAP_SCALE) / fmax(vars->map.width, vars->map.height))
			{
				pixel[X] = map[X] * (fmax(WIN_W, WIN_H) / MINIMAP_SCALE) / fmax(vars->map.width, vars->map.height);
				while (pixel[X] < (map[X] + 1) * (fmax(WIN_W, WIN_H) / MINIMAP_SCALE) / fmax(vars->map.width, vars->map.height))
				{
					if (vars->map.map[map[Y]][map[X]] == FLOOR)
						img_pixel_put(&vars->minimap, pixel[X] + (vars->mm_offset[X] / 2), pixel[Y] + (vars->mm_offset[Y] / 2), MINIMAP_FLOOR);
					else if (vars->map.map[map[Y]][map[X]] == DOOR_CLOSE
						|| vars->map.map[map[Y]][map[X]] == DOOR_OPEN)
						img_pixel_put(&vars->minimap, pixel[X] + (vars->mm_offset[X] / 2), pixel[Y] + (vars->mm_offset[Y] / 2), MINIMAP_DOOR);
					else
						img_pixel_put(&vars->minimap, pixel[X] + (vars->mm_offset[X] / 2), pixel[Y] + (vars->mm_offset[Y] / 2), MINIMAP_WALL);
					pixel[X]++;
				}
				pixel[Y]++;
			}
		}
	}
}

int	initialise_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->img.img = mlx_new_image(vars->mlx, WIN_W, WIN_H);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&vars->img.bpp, &vars->img.line_len, &vars->img.endian);
	vars->win = mlx_new_window(vars->mlx, WIN_W, WIN_H, "cub3D");
	initialise_minimap(vars);
	if (init_textures(vars) != 0)
		return (1);
	return (0);
}
