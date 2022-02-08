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

static void	sort_sprites(t_ray *ray, t_vars *vars)
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

void	raycast_sprite(t_vars *vars, t_ray *ray)
{
	t_sprite_sp	*s;

	s = (t_sprite_sp *)malloc(sizeof(t_sprite_sp));
	ray->sprite_order = (int *)malloc(sizeof(int) * vars->map.sprite_cnt);
	ray->sprite_dist = (float *)malloc(sizeof(float) * vars->map.sprite_cnt);

	for (int i = 0; i < vars->map.sprite_cnt; i++)
	{
		ray->sprite_order[i] = i;
		ray->sprite_dist[i] = ((vars->p.pos_x - vars->map.sprite[i].x) * (vars->p.pos_x - vars->map.sprite[i].x)
			+ (vars->p.pos_y - vars->map.sprite[i].y) * (vars->p.pos_y - vars->map.sprite[i].y));
	}
	sort_sprites(ray, vars);

	for (int i = 0; i < vars->map.sprite_cnt; i++)
	{
		s->sprite_x = vars->map.sprite[ray->sprite_order[i]].x - vars->p.pos_x;
		s->sprite_y = vars->map.sprite[ray->sprite_order[i]].y - vars->p.pos_y;

		s->inv_det = 1.0 / (vars->p.plane_x * vars->p.dir_y - vars->p.plane_y * vars->p.dir_x);

		s->transform_x = s->inv_det * (vars->p.dir_y * s->sprite_x - vars->p.dir_x * s->sprite_y);
		s->transform_y = s->inv_det * (-vars->p.plane_y * s->sprite_x + vars->p.plane_x * s->sprite_y);

		s->sprite_screen_x = (int)((WIN_W / 2) * (1 + s->transform_x / s->transform_y));

		s->sprite_height = abs((int)(WIN_H / (s->transform_y)));

		s->draw_start_y = -s->sprite_height / 2 + WIN_H / 2;
		if (s->draw_start_y < 0)
			s->draw_start_y = 0;
		s->draw_end_y = s->sprite_height / 2 + WIN_H / 2;
		if (s->draw_end_y >= WIN_H)
			s->draw_end_y = WIN_H - 1;

		s->sprite_width = abs((int)(WIN_H / s->transform_y));
		s->draw_start_x = -s->sprite_width / 2 + s->sprite_screen_x;
		if (s->draw_start_x < 0)
			s->draw_start_x = 0;
		s->draw_end_x = s->sprite_width / 2 + s->sprite_screen_x;
		if (s->draw_end_x >= WIN_W)
			s->draw_end_x = WIN_W - 1;

		for (int x = s->draw_start_x; x < s->draw_end_x; x++)
		{
			s->tex_x = (int)((256 * (x - (-s->sprite_width / 2 + s->sprite_screen_x)) * vars->sprite[vars->map.sprite[ray->sprite_order[i]].id][(int)(vars->frame / 10)]->w / s->sprite_width) / 256);
			if (s->transform_y > 0 && x > 0 && x < WIN_W && s->transform_y < ray->z_buffer[x])
			{
				for (int y = s->draw_start_y; y < s->draw_end_y; y++)
				{
					s->d = (y) * 256 - WIN_H * 128 + s->sprite_height * 128;
					s->tex_y = ((s->d * vars->sprite[vars->map.sprite[ray->sprite_order[i]].id][(int)(vars->frame / 10)]->h) / s->sprite_height) / 256;
					s->color = get_pixel_color(&vars->sprite[vars->map.sprite[ray->sprite_order[i]].id][(int)(vars->frame / 10)]->img, s->tex_x, s->tex_y);
					if (s->color != 0x0)
						img_paste_pixel(&vars->img, WIN_W - 1 - x, y, s->color);
				}
			}
		}
	}

	free(s);
	free(ray->sprite_order);
	free(ray->sprite_dist);
}

