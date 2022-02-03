/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:04:36 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/19 15:04:54 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ver_line(t_vars *vars, int x, int draw_start, int draw_end, int color)
{
	int	y;

	y = -1;
	while (++y < WIN_H)
	{
		if (y < draw_start)
			//img_pixel_put(vars->img, x, y, vars->map.crgb);
			img_pixel_put(vars->img, x, y, 0x581845);
		if (y >= draw_start && y < draw_end)
		{
			//img_pixel_put(vars->img, x, y, 0xC70039);
			img_pixel_put(vars->img, x, y, color);
		}
		if (y >= draw_end)
			//img_pixel_put(vars->img, x, y, vars->map.crgb);
			img_pixel_put(vars->img, x, y, 0xFFC30F);
	}
}

static void	raycast(t_vars *vars)
{
	int		x;
	t_ray	ray;

	x = -1;
	while (++x < WIN_W)
	{
		ray.cam_x = (2 * x) / (float)WIN_W - 1;
		ray.dir_x = vars->p.dir_x + vars->p.plane_x * ray.cam_x;
		ray.dir_y = vars->p.dir_y + vars->p.plane_y * ray.cam_x;

		//printf("x: %f, y: %f\n", vars->p.pos_x, vars->p.pos_y);
		ray.map_x = (int)vars->p.pos_x;
		ray.map_y = (int)vars->p.pos_y;
		//printf("x: %d, y: %d\n", ray.map_x, ray.map_y);

		ray.delta_dist_x = (ray.dir_x == 0) ? 1e30 : fabs(1 / ray.dir_x);
		ray.delta_dist_y = (ray.dir_y == 0) ? 1e30 : fabs(1 / ray.dir_y);

		ray.hit = 0;

		if (ray.dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (vars->p.pos_x - ray.map_x) * ray.delta_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1.0 - vars->p.pos_x) * ray.delta_dist_x;
		}
		if (ray.dir_y < 0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (vars->p.pos_y - ray.map_y) * ray.delta_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (ray.map_y + 1.0 - vars->p.pos_y) * ray.delta_dist_y;
		}

		while (ray.hit == 0)
		{
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				ray.map_x += ray.step_x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				ray.map_y += ray.step_y;
				ray.side = 1;
			}

			//printf("x: %d, y: %d\n", ray.map_x, ray.map_y);
			if (vars->map.map[ray.map_y][ray.map_x] == WALL)
				ray.hit = 1;
		}	

		if (ray.side == 0)
			ray.perp_wall_dist = ray.side_dist_x - ray.delta_dist_x;
		else
			ray.perp_wall_dist = ray.side_dist_y - ray.delta_dist_y;

		ray.line_height = (int)(WIN_H / ray.perp_wall_dist);

		ray.draw_start = -ray.line_height / 2 + WIN_H / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + WIN_H / 2;
		if (ray.draw_end >= WIN_H)
			ray.draw_end = WIN_H - 1;

		if (ray.side == 0)
		{
			if (ray.dir_x < 0)
				ray.texture_id = 0;
			else
				ray.texture_id = 1;
		}
		else
		{
			if (ray.dir_y < 0)
				ray.texture_id = 3;
			else
				ray.texture_id = 2;
		}
		//texture()

		int color = 0xC70039;
		if (ray.side == 1)
			color = color / 2;
		draw_ver_line(vars, x, ray.draw_start, ray.draw_end, color);
	}
}

static void	draw_menu(t_vars *vars)
{
	int		y;
	void	*mlx;
	void	*win;

	mlx = vars->mlx;
	win = vars->win;
	y = 0;
	mlx_string_put(mlx, win, 15, y += 15, WHITE, "Controls:");
	mlx_string_put(mlx, win, 15, y += 25, WHITE, "Reset: R");
	mlx_string_put(mlx, win, 15, y += 25, WHITE, "Move: W, A, S, D");
	mlx_string_put(mlx, win, 15, y += 25, WHITE, "Look: mouse");
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
	raycast(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	draw_minimap(vars);
	draw_menu(vars);
}
