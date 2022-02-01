/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:19:47 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/01 13:21:25 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int	mouse_hook(int x, int y, t_vars *vars)
{
	(void)vars;
	if (x < 0 || y < 0)
		return (1);
	printf("key: x -> %d | y -> %d\n", x, y);
	return (0);
}

int	mlx_main(t_vars *vars)
{
	printf("Starting minilibx...\n");
	if (initialise_vars(vars))
	{
		free_all(vars);
		perror_exit("malloc");
	}
	initialise_mlx(vars);
	mlx_hook(vars->win, 2, 1L << 0, key_hook, vars);
	mlx_hook(vars->win, 17, 1L << 17, close_win, vars);
	draw(vars);
	mlx_hook(vars->win, 6, 1L << 4, mouse_hook, &vars); // MOUSE MOVE HOOK;
	mlx_loop(vars->mlx);
	free_all(vars);
	return (0);
}
