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

static int	load_texture(t_vars *vars, t_tex *texture, char *xpm_path)
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

static int	load_sprite(t_vars *vars, t_tex **texture, char *xpm_path)
{
	int	ret;

	*texture = (t_tex *)malloc(sizeof(t_tex));
	ret = load_texture(vars, *texture, xpm_path);
	return (ret);
}

static int	init_sprites(t_vars *vars)
{
	int		i;
	int		j;

	i = 0;
	while (vars->map.sprites[i] != NULL)
		i++;
	vars->sprite = (t_tex ***)ft_calloc(i + 1, sizeof(t_tex **));
	i = -1;
	while (vars->map.sprites[++i] != NULL)
	{
		j = 0;
		while (vars->map.sprites[i][j] != NULL)
			j++;
		vars->sprite[i] = (t_tex **)ft_calloc(j + 1, sizeof(t_tex *));
		j = -1;
		while (vars->map.sprites[i][++j] != NULL)
		{
			if (load_sprite(vars, &vars->sprite[i][j], vars->map.sprites[i][j])
				!= 0)
				return (1);
		}
	}
	return (0);
}

int	init_textures(t_vars *vars)
{
	if (load_texture(vars, &vars->tex[TEX_NO], vars->map.no) != 0
		|| load_texture(vars, &vars->tex[TEX_SO], vars->map.so) != 0
		|| load_texture(vars, &vars->tex[TEX_WE], vars->map.we) != 0
		|| load_texture(vars, &vars->tex[TEX_EA], vars->map.ea) != 0
		|| load_texture(vars, &vars->tex[TEX_DOOR], vars->map.door) != 0)
		return (1);
	if (init_sprites(vars) != 0)
		return (1);
	return (0);
}
