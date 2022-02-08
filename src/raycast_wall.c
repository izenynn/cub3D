/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:48:05 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/08 12:48:06 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_if_ray_hit_wall(t_vars *vars, t_ray *ray, int x)
{
	if (vars->map->map[ray->map_y][ray->map_x] == WALL
		|| vars->map->map[ray->map_y][ray->map_x] == DOOR_CLOSE)
		ray->hit = 1;
	if (vars->map->map[ray->map_y][ray->map_x] == DOOR_CLOSE
		|| vars->map->map[ray->map_y][ray->map_x] == DOOR_OPEN)
	{
		ray->hit_door = 1;
		if (x == WIN_W / 2)
		{
			vars->door_hit[X] = ray->map_x;
			vars->door_hit[Y] = ray->map_y;
		}
	}
}

static void	dda(t_vars *vars, t_ray *ray, int x)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		check_if_ray_hit_wall(vars, ray, x);
	}
}

static void	calculate_screen_line(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

static void	calculate_texture_data(t_vars *vars, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = vars->p.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = vars->p.pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor((ray->wall_x));
	ray->tex_x = (int)(ray->wall_x * (float)TEX_W);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = vars->tex[ray->texture_id].w - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = vars->tex[ray->texture_id].w - ray->tex_x - 1;
	ray->step = 1.0 * vars->tex[ray->texture_id].h / ray->line_height;
	ray->tex_pos
		= (ray->draw_start - WIN_H / 2 + ray->line_height / 2) * ray->step;
}

void	raycast_wall(t_vars *vars, t_ray *ray)
{
	int		x;

	x = -1;
	while (++x < WIN_W)
	{
		init_ray(vars, ray, x);
		init_step_and_sidedist(vars, ray);
		dda(vars, ray, x);
		calculate_screen_line(ray);
		calculate_texture_id(vars, ray);
		calculate_texture_data(vars, ray);
		draw_ver_line(vars, x, ray);
		ray->z_buffer[x] = ray->perp_wall_dist;
	}
}
