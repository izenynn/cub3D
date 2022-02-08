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

void	free_vars(t_vars *vars)
{
	free_map(&vars->map);
	free(vars);
}

void	free_all(t_vars *vars)
{
	int	i;
	int	j;

	mlx_destroy_image(vars->mlx, vars->minimap.img);
	mlx_destroy_image(vars->mlx, vars->mm_player.img);
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_NO].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_SO].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_WE].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_EA].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_DOOR].img.img);
	i = -1;
	while (vars->sprite != NULL && vars->sprite[++i] != NULL)
	{
		j = -1;
		while (vars->sprite[i][++j] != NULL)
		{
			mlx_destroy_image(vars->mlx, vars->sprite[i][j]->img.img);
			free(vars->sprite[i][j]);
		}
		free(vars->sprite[i]);
	}
	free(vars->sprite);
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars);
}

int	initialise_vars(t_vars *vars)
{
	vars->frame = -1;
	vars->sprite = NULL;
	player_init(vars);
	return (0);
}
