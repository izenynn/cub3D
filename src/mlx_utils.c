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

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	int	pixel;

	if (y >= WIN_H || x >= WIN_W || y < 0 || x < 0)
		return ;
	pixel = (y * img->line_len) + (x * (img->bpp / 8));
	if (img->endian == 1)
	{
		img->addr[pixel + 0] = (color >> 24);
		img->addr[pixel + 1] = (color >> 16) & 0xFF;
		img->addr[pixel + 2] = (color >> 8) & 0xFF;
		img->addr[pixel + 3] = (color) & 0xFF;
	}
	else if (img->endian == 0)
	{
		img->addr[pixel + 0] = (color) & 0xFF;
		img->addr[pixel + 1] = (color >> 8) & 0xFF;
		img->addr[pixel + 2] = (color >> 16) & 0xFF;
		img->addr[pixel + 3] = (color >> 24);
	}
}

void	img_paste_pixel(t_img *img, int x, int y, int pixel)
{
	int	img_pixel;

	if (y >= WIN_H || x >= WIN_W || y < 0 || x < 0)
		return ;
	//img_pixel = (y * img.line_len) + (x * (img.bpp / 8));
	//img.addr[img_pixel] = pixel;

	(void)img_pixel;
	char *dst = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)dst = pixel;

	/*int endian = 0;
	if (endian == 1)
	{
		img.addr[img_pixel + 0] = (pixel >> 24);
		img.addr[img_pixel + 1] = (pixel >> 16) & 0xFF;
		img.addr[img_pixel + 2] = (pixel >> 8) & 0xFF;
		img.addr[img_pixel + 3] = (pixel) & 0xFF;
	}
	else if (endian == 0)
	{
		img.addr[img_pixel + 0] = (pixel) & 0xFF;
		img.addr[img_pixel + 1] = (pixel >> 8) & 0xFF;
		img.addr[img_pixel + 2] = (pixel >> 16) & 0xFF;
		img.addr[img_pixel + 3] = (pixel >> 24);
	}*/
}
