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
