/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:16:32 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/08 18:16:33 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_vars *vars, t_ray *ray, int x)
{
	ray->cam_x = (2 * x) / (float)WIN_W - 1;
	ray->dir_x = vars->p.dir_x + vars->p.plane_x * ray->cam_x;
	ray->dir_y = vars->p.dir_y + vars->p.plane_y * ray->cam_x;
		ray->map_x = (int)vars->p.pos_x;
	ray->map_y = (int)vars->p.pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	ray->hit_door = 0;
}

void	init_step_and_sidedist(t_vars *vars, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (vars->p.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x
			= (ray->map_x + 1.0 - vars->p.pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (vars->p.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y
			= (ray->map_y + 1.0 - vars->p.pos_y) * ray->delta_dist_y;
	}
}

void	calculate_texture_id(t_vars *vars, t_ray *ray)
{
	if (vars->map.map[ray->map_y][ray->map_x] == DOOR_CLOSE)
		ray->texture_id = TEX_DOOR;
	else if ((ray->map_y >= 1 && ray->side == 1 && ray->dir_y >= 0
			&& vars->map.map[ray->map_y - 1][ray->map_x] == DOOR_OPEN)
		|| (ray->map_x >= 1 && ray->side == 0 && ray->dir_x >= 0
			&& vars->map.map[ray->map_y][ray->map_x - 1] == DOOR_OPEN))
		ray->texture_id = TEX_DOOR;
	else if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			ray->texture_id = TEX_WE;
		else
			ray->texture_id = TEX_EA;
	}
	else
	{
		if (ray->dir_y < 0)
			ray->texture_id = TEX_NO;
		else
			ray->texture_id = TEX_SO;
	}
}

void	draw_ver_line(t_vars *vars, int x, t_ray *ray)
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
			ray->tex_y = (int)ray->tex_pos & (tex->h - 1);
			ray->tex_pos += ray->step;
			color = get_pixel_color(&tex->img, ray->tex_x, ray->tex_y);
			img_paste_pixel(&vars->img, WIN_W - 1 - x, y, color);
		}
		if (y > ray->draw_end)
			img_pixel_put(&vars->img, WIN_W - 1 - x, y, vars->map.frgb);
	}
}
