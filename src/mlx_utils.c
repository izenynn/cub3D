/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:55:04 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/13 14:23:37 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pixel_put(t_img img, int x, int y, int color)
{
	int	pixel;

	if (y >= WIN_H || x >= WIN_W || y < 0 || x < 0)
		return ;
	pixel = (y * img.sz_l) + (x * (img.bpp / 8));
	if (img.endian == 1)
	{
		img.addr[pixel + 0] = (color >> 24);
		img.addr[pixel + 1] = (color >> 16) & 0xFF;
		img.addr[pixel + 2] = (color >> 8) & 0xFF;
		img.addr[pixel + 3] = (color) & 0xFF;
	}
	else if (img.endian == 0)
	{
		img.addr[pixel + 0] = (color) & 0xFF;
		img.addr[pixel + 1] = (color >> 8) & 0xFF;
		img.addr[pixel + 2] = (color >> 16) & 0xFF;
		img.addr[pixel + 3] = (color >> 24);
	}
}