/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:48:12 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/08 12:48:13 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sort_sprites(t_vars *vars, t_ray *ray)
{
	float	dist;
	int		order;
	int		sprite;
	int		i;

	i = -1;
	while (++i < vars->map.sprite_cnt - 1)
	{
		sprite = -1;
		while (++sprite < vars->map.sprite_cnt - 1)
		{
			if (ray->sprite_dist[sprite] < ray->sprite_dist[sprite + 1])
			{
				dist = ray->sprite_dist[sprite + 1];
				ray->sprite_dist[sprite + 1] = ray->sprite_dist[sprite];
				ray->sprite_dist[sprite] = dist;
				order = ray->sprite_order[sprite + 1];
				ray->sprite_order[sprite + 1] = ray->sprite_order[sprite];
				ray->sprite_order[sprite] = order;
			}
		}
	}
}

static void	calculate_sprite_dimensions_on_screen(t_sprite_sp *s)
{
	s->height = abs((int)(WIN_H / (s->transform_y)));
	s->draw_start_y = -s->height / 2 + WIN_H / 2;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->height / 2 + WIN_H / 2;
	if (s->draw_end_y >= WIN_H)
		s->draw_end_y = WIN_H - 1;
	s->width = abs((int)(WIN_H / s->transform_y));
	s->draw_start_x = -s->width / 2 + s->screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->width / 2 + s->screen_x;
	if (s->draw_end_x >= WIN_W)
		s->draw_end_x = WIN_W - 1;
}

static void	draw_sprite(t_vars *vars, t_ray *ray, t_sprite_sp *s)
{
	int	x;
	int	y;

	x = s->draw_start_x - 1;
	while (++x < s->draw_end_x)
	{
		s->tex_x = (int)((256 * (x - (-s->width / 2 + s->screen_x))
					* vars->sprite[s->id][s->frame]->w / s->width) / 256);
		if (s->transform_y > 0 && x > 0
			&& x < WIN_W && s->transform_y < ray->z_buffer[x])
		{
			y = s->draw_start_y - 1;
			while (++y < s->draw_end_y)
			{
				s->d = (y) * 256 - WIN_H * 128 + s->height * 128;
				s->tex_y = ((s->d * vars->sprite[s->id][s->frame]->h)
						/ s->height) / 256;
				s->color = get_pixel_color(&vars->sprite[s->id][s->frame]->img,
						s->tex_x, s->tex_y);
				if (s->color != 0x0)
					img_paste_pixel(&vars->img, WIN_W - 1 - x, y, s->color);
			}
		}
	}
}

static void	project_and_draw(t_vars *vars, t_ray *ray, t_sprite_sp *s, int i)
{
	s->x = vars->map.sprite[ray->sprite_order[i]].x - vars->p.pos_x;
	s->y = vars->map.sprite[ray->sprite_order[i]].y - vars->p.pos_y;
	s->inv_det = 1.0
		/ (vars->p.plane_x * vars->p.dir_y - vars->p.plane_y * vars->p.dir_x);
	s->transform_x = s->inv_det * (vars->p.dir_y * s->x - vars->p.dir_x * s->y);
	s->transform_y = s->inv_det
		* (-vars->p.plane_y * s->x + vars->p.plane_x * s->y);
	s->screen_x = (int)((WIN_W / 2) * (1 + s->transform_x / s->transform_y));
	calculate_sprite_dimensions_on_screen(s);
	s->id = vars->map.sprite[ray->sprite_order[i]].id;
	s->frame = (int)(vars->frame / 10);
	draw_sprite(vars, ray, s);
}

void	raycast_sprite(t_vars *vars, t_ray *ray)
{
	int			i;
	t_sprite_sp	*s;

	s = (t_sprite_sp *)malloc(sizeof(t_sprite_sp));
	ray->sprite_order = (int *)malloc(sizeof(int) * vars->map.sprite_cnt);
	ray->sprite_dist = (float *)malloc(sizeof(float) * vars->map.sprite_cnt);
	i = -1;
	while (++i < vars->map.sprite_cnt)
	{
		ray->sprite_order[i] = i;
		ray->sprite_dist[i] = ((vars->p.pos_x - vars->map.sprite[i].x)
				* (vars->p.pos_x - vars->map.sprite[i].x)
				+ (vars->p.pos_y - vars->map.sprite[i].y)
				* (vars->p.pos_y - vars->map.sprite[i].y));
	}
	sort_sprites(vars, ray);
	i = -1;
	while (++i < vars->map.sprite_cnt)
		project_and_draw(vars, ray, s, i);
	free(s);
	free(ray->sprite_order);
	free(ray->sprite_dist);
}
