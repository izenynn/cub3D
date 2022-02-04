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
}

void	free_all(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->minimap.img);
	mlx_destroy_image(vars->mlx, vars->mm_player.img);
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_image(vars->mlx, vars->tex[0].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[1].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[2].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[3].img.img);
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
	player_init(vars);
	return (0);
}
