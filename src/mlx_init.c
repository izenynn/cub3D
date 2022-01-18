/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:37:56 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/13 14:17:35 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void initialise_minimap(t_vars *vars)
{
	vars->minimap.img = mlx_new_image(vars->mlx,
		WIN_W / MINIMAP_SCALE, WIN_H / MINIMAP_SCALE);
	vars->minimap.addr = mlx_get_data_addr(vars->minimap.img,
			&vars->minimap.bpp, &vars->minimap.sz_l, &vars->minimap.endian);
}

void	initialise_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->img.img = mlx_new_image(vars->mlx, WIN_W, WIN_H);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&vars->img.bpp, &vars->img.sz_l, &vars->img.endian);
	vars->win = mlx_new_window(vars->mlx, WIN_W, WIN_H, "cub3D");
	initialise_minimap(vars);
}
