/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:19:47 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/09 15:20:50 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mlx_main(t_vars *vars)
{
	if (initialise_vars(vars))
	{
		free_all(vars);
		perror_exit("malloc");
	}
	if (initialise_mlx(vars) != 0)
		return (1);
	mlx_hook(vars->win, 2, (1L << 0), key_press_hook, vars);
	mlx_hook(vars->win, 3, (1L << 1), key_relase_hook, vars);
	mlx_hook(vars->win, 17, (1L << 17), close_win, vars);
	mlx_hook(vars->win, 6, (1L << 6), mouse_hook, vars);
	mlx_loop_hook(vars->mlx, game_loop, vars);
	mlx_loop(vars->mlx);
	free_all(vars);
	return (0);
}
