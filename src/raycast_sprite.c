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
		float sprite_x = vars->map.sprite[ray->sprite_order[i]].x - vars->p.pos_x;
		float sprite_y = vars->map.sprite[ray->sprite_order[i]].y - vars->p.pos_y;

		float inv_det = 1.0 / (vars->p.plane_x * vars->p.dir_y - vars->p.plane_y * vars->p.dir_x);

		float transform_x = inv_det * (vars->p.dir_y * sprite_x - vars->p.dir_x * sprite_y);
		float transform_y = inv_det * (-vars->p.plane_y * sprite_x + vars->p.plane_x * sprite_y);

		int sprite_screen_x = (int)((WIN_W / 2) * (1 + transform_x / transform_y));

		int sprite_height = abs((int)(WIN_H / (transform_y)));

		int draw_start_y = -sprite_height / 2 + WIN_H / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + WIN_H / 2;
		if (draw_end_y >= WIN_H)
			draw_end_y = WIN_H - 1;

		int sprite_width = abs((int)(WIN_H / transform_y));
		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x >= WIN_W)
			draw_end_x = WIN_W - 1;

		for (int x = draw_start_x; x < draw_end_x; x++)
		{
			int tex_x = (int)((256 * (x - (-sprite_width / 2 + sprite_screen_x)) * vars->sprite[vars->map.sprite[ray->sprite_order[i]].id][(int)(vars->frame / 10)]->w / sprite_width) / 256);
			if (transform_y > 0 && x > 0 && x < WIN_W && transform_y < ray->z_buffer[x])
			{
				for (int y = draw_start_y; y < draw_end_y; y++)
				{
					int d = (y) * 256 - WIN_H * 128 + sprite_height * 128;
					int tex_y = ((d * vars->sprite[vars->map.sprite[ray->sprite_order[i]].id][(int)(vars->frame / 10)]->h) / sprite_height) / 256;
					int color = get_pixel_color(&vars->sprite[vars->map.sprite[ray->sprite_order[i]].id][(int)(vars->frame / 10)]->img, tex_x, tex_y);
					if (color != 0x0)
						img_paste_pixel(&vars->img, WIN_W - 1 - x, y, color);
				}
			}
		}
	}
}

