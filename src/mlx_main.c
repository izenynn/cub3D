/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:19:47 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/13 12:41:39 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int mouse_hook(int keycode, t_vars *vars)
{
	(void)vars;
	printf("key: %d\n", keycode);
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
	mlx_mouse_hook(vars->win, mouse_hook, &vars);
	int x,y;
	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
	printf("x-> %d | y-> %d\n", x, y);
	mlx_loop(vars->mlx);
	free_all(vars);
	return (0);
}
