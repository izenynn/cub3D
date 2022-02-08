/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:54:55 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/08 18:54:56 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_inner_map_offset(t_vars *vars)
{
	vars->mm_offset[X] = 0;
	vars->mm_offset[Y] = 0;
	if (vars->map->width > vars->map->height)
		vars->mm_offset[Y] = (vars->map->width - vars->map->height)
			* (fmax(WIN_W, WIN_H) / MINIMAP_SCALE / vars->map->width);
	else if (vars->map->height > vars->map->width)
		vars->mm_offset[X] = (vars->map->height - vars->map->width)
			* (fmax(WIN_W, WIN_H) / MINIMAP_SCALE / vars->map->height);
}

void	init_mlx_image(t_vars *vars)
{
	vars->minimap.img = mlx_new_image(vars->mlx,
			fmax(WIN_W, WIN_H) / MINIMAP_SCALE,
			fmax(WIN_W, WIN_H) / MINIMAP_SCALE);
	vars->minimap.addr = mlx_get_data_addr(
			vars->minimap.img, &vars->minimap.bpp,
			&vars->minimap.line_len, &vars->minimap.endian);
	vars->mm_player.img = mlx_new_image(vars->mlx,
			fmax(WIN_W, WIN_H) / MINIMAP_SCALE,
			fmax(WIN_W, WIN_H) / MINIMAP_SCALE);
	vars->mm_player.addr = mlx_get_data_addr(
			vars->mm_player.img, &vars->mm_player.bpp,
			&vars->mm_player.line_len, &vars->mm_player.endian);
}

void	draw_background(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
	{
		x = -1;
		while (++x < fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
			img_pixel_put(&vars->minimap, x, y, MINIMAP_WALL);
	}
}
