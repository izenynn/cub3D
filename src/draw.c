/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:04:36 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/13 13:52:17 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_menu(t_vars *vars)
{
	int		y;
	void	*mlx;
	void	*win;

	mlx = vars->mlx;
	win = vars->win;
	y = 0;
	mlx_string_put(mlx, win, 15, y += 15, WHITE, "Controls:");
	mlx_string_put(mlx, win, 15, y += 50, WHITE, "Reset: R");
	mlx_string_put(mlx, win, 15, y += 25, WHITE, "Move: W, A, S, D");
	mlx_string_put(mlx, win, 15, y += 25, WHITE, "Open doors: F");
}

/* draw minimap on upper right corner */
static void draw_minimap(t_vars *vars)
{
	(void)vars;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->minimap.img,
			WIN_W - (vars->minimap.line_len / vars->minimap.bpp * 8) - 15, 15);
}

/* draw all on screen */
void	draw(t_vars *vars)
{
	ft_bzero(vars->img.addr, WIN_H * WIN_W * (vars->img.bpp / 8));
	// TODO draw
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	draw_minimap(vars);
	draw_menu(vars);
}
