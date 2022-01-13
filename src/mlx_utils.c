/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:55:04 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/13 13:56:32 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pixel_put(t_vars *vars, int x, int y, int color)
{
	int	pixel;

	if (y >= WIN_H || x >= WIN_W || y < 0 || x < 0)
		return ;
	pixel = (y * vars->img.sz_l) + (x * (vars->img.bpp / 8));
	if (vars->img.endian == 1)
	{
		vars->img.addr[pixel + 0] = (color >> 24);
		vars->img.addr[pixel + 1] = (color >> 16) & 0xFF;
		vars->img.addr[pixel + 2] = (color >> 8) & 0xFF;
		vars->img.addr[pixel + 3] = (color) & 0xFF;
	}
	else if (vars->img.endian == 0)
	{
		vars->img.addr[pixel + 0] = (color) & 0xFF;
		vars->img.addr[pixel + 1] = (color >> 8) & 0xFF;
		vars->img.addr[pixel + 2] = (color >> 16) & 0xFF;
		vars->img.addr[pixel + 3] = (color >> 24);
	}
}
