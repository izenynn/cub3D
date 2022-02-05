/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:22:48 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/13 12:58:17 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	free_vars(t_vars *vars)
{
	free(vars);
}

void	free_map(t_map *map)
{
	free_split(map->map);
	free_split(map->buffer);
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	free(map->door);
}

void	free_all(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->minimap.img);
	mlx_destroy_image(vars->mlx, vars->mm_player.img);
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_NO].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_SO].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_WE].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_EA].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_DOOR].img.img);

	// vars->sprite will be null if a sprite is not especified in the map
	if (vars->sprite != NULL)
	{
		mlx_destroy_image(vars->mlx, vars->sprite[0].img.img);
		mlx_destroy_image(vars->mlx, vars->sprite[1].img.img);
		mlx_destroy_image(vars->mlx, vars->sprite[2].img.img);
		mlx_destroy_image(vars->mlx, vars->sprite[3].img.img);
		mlx_destroy_image(vars->mlx, vars->sprite[4].img.img);
		mlx_destroy_image(vars->mlx, vars->sprite[5].img.img);
	}

	mlx_destroy_window(vars->mlx, vars->win);
	free_map(&vars->map);
	free_vars(vars);
}

void	reset_vars(t_vars *vars)
{
	(void)vars;
}

int	initialise_vars(t_vars *vars)
{
	reset_vars(vars);
	vars->frame = -1;
	player_init(vars);
	return (0);
}
