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

static int	load_sprite(t_vars *vars, t_tex **texture, char *xpm_path)
{
	int	ret;

	*texture = (t_tex *)malloc(sizeof(t_tex));
	ret = load_xpm(vars, *texture, xpm_path);
	return (ret);
}

int	init_textures(t_vars *vars)
{
	int	i;
	int	j;

	if (load_xpm(vars, &vars->tex[TEX_NO], vars->map.no) != 0
		|| load_xpm(vars, &vars->tex[TEX_SO], vars->map.so) != 0
		|| load_xpm(vars, &vars->tex[TEX_WE], vars->map.we) != 0
		|| load_xpm(vars, &vars->tex[TEX_EA], vars->map.ea) != 0
		|| load_xpm(vars, &vars->tex[TEX_DOOR], vars->map.door) != 0)
		return (1);
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
			if (load_sprite(vars, &vars->sprite[i][j], vars->map.sprites[i][j]) != 0)
				return (1);
		}
	}

	//printf("ENTER\n");
	//for (int k = 0; vars->sprite[k] != NULL; k++) {
	//	printf("vars->sprite[%d] = %p\n", k, (void *)vars->sprite[k]);
	//	for (int l = 0; vars->sprite[k][l] != NULL; l++) {
	//		printf("\tvars->sprite[%d][%d] = %p\n", k, l, (void *)vars->sprite[k][l]);
	//	}
	//}
	//printf("LEAVE\n");

	//if (vars->sprite != NULL)
	//{
	//	if (load_xpm(vars, &vars->sprite[0][0], vars->map.sprite[0][0]) != 0
	//		|| load_xpm(vars, &vars->sprite[0][1], vars->map.sprite[0][1]) != 0
	//		|| load_xpm(vars, &vars->sprite[0][2], vars->map.sprite[0][2]) != 0
	//		|| load_xpm(vars, &vars->sprite[0][3], vars->map.sprite[0][3]) != 0
	//		|| load_xpm(vars, &vars->sprite[0][4], vars->map.sprite[0][4]) != 0
	//		|| load_xpm(vars, &vars->sprite[0][5], vars->map.sprite[0][5]) != 0)
	//		return (1);
	//}
	return (0);
}
