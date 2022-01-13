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
	(void)vars;
}

void	free_all(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_image(vars->mlx, vars->img.img);
	free_vars(vars);
}

void	reset_vars(t_vars *vars)
{
	(void)vars;
}

int	initialise_vars(t_vars *vars)
{
	reset_vars(vars);
	return (0);
}
