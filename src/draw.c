/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:04:36 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/08 11:48:24 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ver_line(t_vars *vars, int x, t_ray *ray)
{
	int		y;
	int		color;
	t_tex	*tex;

	tex = &vars->tex[ray->texture_id];
	y = -1;
	while (++y < WIN_H)
	{
		if (y < ray->draw_start)
			img_pixel_put(&vars->img, WIN_W - 1 - x, y, vars->map.crgb);
		if (y >= ray->draw_start && y <= ray->draw_end)
		{
			//img_pixel_put(vars->img, x, y, 0xC70039);
			//img_pixel_put(vars->img, x, y, color);
			ray->tex_y = (int)ray->tex_pos & (tex->h - 1);
			ray->tex_pos += ray->step;
			//color = tex->img.addr[tex->h * ray->tex_y + ray->tex_x];
			//color = tex->img.addr[tex->h * ray->tex_y + ray->tex_x];
			//pixel = (y * img.line_len) + (x * (img.bpp / 8));

			//pixel = tex->img.addr[(ray->tex_y * tex->img.line_len) + (ray->tex_x * (tex->img.bpp / 8))];
			color = get_pixel_color(&tex->img, ray->tex_x, ray->tex_y);
			//printf("color: %x\n", color);
			img_paste_pixel(&vars->img, WIN_W - 1 - x, y, color);
		}
		if (y > ray->draw_end)
			img_pixel_put(&vars->img, WIN_W - 1 - x, y, vars->map.frgb);
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
		ray.hit_door = 0;

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
			if (vars->map.map[ray.map_y][ray.map_x] == WALL
				|| vars->map.map[ray.map_y][ray.map_x] == DOOR_CLOSE)
				ray.hit = 1;
			if (vars->map.map[ray.map_y][ray.map_x] == DOOR_CLOSE
				|| vars->map.map[ray.map_y][ray.map_x] == DOOR_OPEN)
			{
				ray.hit_door = 1;
				if (x == WIN_W / 2)
				{
					vars->door_hit[X] = ray.map_x;
					vars->door_hit[Y] = ray.map_y;
				}
			}
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

		// texture
		if (vars->map.map[ray.map_y][ray.map_x] == DOOR_CLOSE)
			ray.texture_id = TEX_DOOR;
		else if ((ray.map_y >= 1 && ray.side == 1 && ray.dir_y >= 0 && vars->map.map[ray.map_y - 1][ray.map_x] == DOOR_OPEN)
			|| (ray.map_x >= 1 && ray.side == 0 && ray.dir_x >= 0 && vars->map.map[ray.map_y][ray.map_x - 1] == DOOR_OPEN))
			ray.texture_id = TEX_DOOR;
		else if (ray.side == 0)
		{
			if (ray.dir_x < 0)
				ray.texture_id = TEX_WE;
			else
				ray.texture_id = TEX_EA;
		}
		else
		{
			if (ray.dir_y < 0)
				ray.texture_id = TEX_NO;
			else
				ray.texture_id = TEX_SO;
		}
		//texture()
		if (ray.side == 0)
			ray.wall_x = vars->p.pos_y + ray.perp_wall_dist * ray.dir_y;
		else
			ray.wall_x = vars->p.pos_x + ray.perp_wall_dist * ray.dir_x;
		ray.wall_x -= floor((ray.wall_x));
		
		ray.tex_x = (int)(ray.wall_x * (float)TEX_W);
		if (ray.side == 0 && ray.dir_x > 0)
			ray.tex_x = vars->tex[ray.texture_id].w - ray.tex_x - 1;
		if (ray.side == 1 && ray.dir_y < 0)
			ray.tex_x = vars->tex[ray.texture_id].w - ray.tex_x - 1;

		ray.step = 1.0 * vars->tex[ray.texture_id].h / ray.line_height;
		ray.tex_pos = (ray.draw_start - WIN_H / 2 + ray.line_height / 2) * ray.step;

		//int color = 0xC70039;
		//if (ray.side == 1)
		//	color = color / 2;
		//draw_ver_line(vars, x, ray.draw_start, ray.draw_end);
		draw_ver_line(vars, x, &ray);

		// sprites
		ray.z_buffer[x] = ray.perp_wall_dist;
	}

	raycast_sprite(vars, &ray);
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
	mlx_string_put(mlx, win, 15, y += 25, WHITE, "Look: Mouse / Arrows");
	mlx_string_put(mlx, win, 15, y += 25, WHITE, "Open / Close doors: E");
}

void	draw_square(t_img *img, int coords[2], float side_len, int color)
{
	float	x1;
	float	y1;

	y1 = -1;
	while (++y1 < side_len)
	{
		x1 = -1;
		while (++x1 < side_len)
			img_pixel_put(img, coords[X] + x1, coords[Y] + y1, color);
	}
}

/* draw minimap on upper right corner */
static void	draw_minimap(t_vars *vars)
{
	int	side_len;
	int	screen_pos[2];
	int	it[2];

	it[Y] = -1;
	while (++it[Y] < fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
	{
		it[X] = -1;
		while (++it[X] < fmax(WIN_W, WIN_H) / MINIMAP_SCALE)
			img_pixel_put(&vars->mm_player, it[X], it[Y], get_pixel_color(&vars->minimap, it[X], it[Y]));
	}
	screen_pos[X] = (vars->mm_offset[X] / 2) + (vars->p.pos_x *
		((vars->minimap.line_len / vars->minimap.bpp * 8) / fmax(vars->map.width, vars->map.height)));
	screen_pos[Y] = (vars->mm_offset[Y] / 2) + (vars->p.pos_y *
		((vars->minimap.line_len / vars->minimap.bpp * 8) / fmax(vars->map.width, vars->map.height)));
	side_len = 5;
	screen_pos[X] -= side_len / 2;
	screen_pos[Y] -= side_len / 2;
	draw_square(&vars->mm_player, screen_pos, side_len, 0xFF0000);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->mm_player.img,
			WIN_W - (vars->mm_player.line_len / vars->mm_player.bpp * 8) - 15, 15);
}

static void	draw_cross(t_vars *vars)
{
	int color;
	int side_len;
	int coords[2];

	color = 0xFFFFFF;
	side_len = 10;
	coords[X] = WIN_W / 2 - side_len / 2;
	coords[Y] = WIN_H / 2 - side_len / 2;

	draw_square(&vars->img, coords, side_len, color);
}

/* draw all on screen */
void	draw(t_vars *vars)
{
	vars->door_hit[X] = -1;
	vars->door_hit[Y] = -1;
	ft_bzero(vars->img.addr, WIN_H * WIN_W * (vars->img.bpp / 8));
	raycast(vars);
	draw_cross(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	draw_minimap(vars);
	draw_menu(vars);
}
