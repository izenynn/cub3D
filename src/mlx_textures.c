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
	if (xpm_path == NULL)
		return (error_ret("xpm path is null", 1));
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
	if (load_xpm(vars, &vars->tex[TEX_NO], vars->map.no) != 0
		|| load_xpm(vars, &vars->tex[TEX_SO], vars->map.so) != 0
		|| load_xpm(vars, &vars->tex[TEX_WE], vars->map.we) != 0
		|| load_xpm(vars, &vars->tex[TEX_EA], vars->map.ea) != 0
		|| load_xpm(vars, &vars->tex[TEX_DOOR], vars->map.door) != 0)
		return (1);
	if (vars->sprite != NULL)
	{
		if (load_xpm(vars, &vars->sprite[0], vars->map.sprite[0]) != 0
			|| load_xpm(vars, &vars->sprite[1], vars->map.sprite[1]) != 0
			|| load_xpm(vars, &vars->sprite[2], vars->map.sprite[2]) != 0
			|| load_xpm(vars, &vars->sprite[3], vars->map.sprite[3]) != 0
			|| load_xpm(vars, &vars->sprite[4], vars->map.sprite[4]) != 0
			|| load_xpm(vars, &vars->sprite[5], vars->map.sprite[5]) != 0)
			return (1);
	}
	return (0);
}
