/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:19:47 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/19 09:24:55 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_xpm(t_vars *vars, t_tex *texture, char *xpm_path)
{
	texture->img.img = mlx_xpm_file_to_image(vars->mlx, xpm_path,
		&texture->w, &texture->h);
	if (texture->img.img == NULL)
		return (error_ret("failed to convert xpm file to mlx image", 1));
	texture->img.addr = mlx_get_data_addr(texture->img.img, &texture->img.bpp,
		&texture->img.line_len, &texture->img.endian);
	if (texture->img.addr == NULL)
		return (error_ret("failed to get mlx image address", 1));
	return (0);
}

int	init_textures(t_vars *vars)
{
	if (load_xpm(vars, &vars->tex[NO], vars->map.no) != 0)
		return (1);
	if (load_xpm(vars, &vars->tex[SO], vars->map.so) != 0)
		return (1);
	if (load_xpm(vars, &vars->tex[WE], vars->map.we) != 0)
		return (1);
	if (load_xpm(vars, &vars->tex[EA], vars->map.ea) != 0)
		return (1);
	return (0);
}
