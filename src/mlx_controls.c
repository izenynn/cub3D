#include "cub3d.h"

void	handle_move(int keycode, t_vars *vars)
{
	t_p		*p;
	char	**map;

	p = &vars->p;
	map = vars->map.map;
	if (keycode == KEY_W)
	{
		if (map[(int)p->pos_y][(int)(p->pos_x + p->dir_x * SPEED)] == FLOOR)
			p->pos_x += p->dir_x * SPEED;
		if (map[(int)(p->pos_y + p->dir_y * SPEED)][(int)p->pos_x] == FLOOR)
			p->pos_y += p->dir_y * SPEED;
	}
	else if (keycode == KEY_S)
	{
		//printf("pos_x: %d, pos_x speed: %d\n", (int)p->pos_x, (int)(p->pos_x + p->dir_x * SPEED));
		//printf("pos_y: %d, pos_y speed: %d\n", (int)p->pos_y, (int)(p->pos_y + p->dir_y * SPEED));
		if (map[(int)p->pos_y][(int)(p->pos_x - p->dir_x * SPEED)] == FLOOR)
			p->pos_x -= p->dir_x * SPEED;
		if (map[(int)(p->pos_y - p->dir_y * SPEED)][(int)p->pos_x] == FLOOR)
			p->pos_y -= p->dir_y * SPEED;
	}
}

void	handle_sidemove(int keycode, t_vars *vars)
{
	t_p		*p;
	char	**map;

	p = &vars->p;
	map = vars->map.map;
	if (keycode == KEY_A)
	{
		if (map[(int)p->pos_y][(int)(p->pos_x - p->plane_x * SPEED)] == FLOOR)
			p->pos_x -= p->plane_x * SPEED;
		if (map[(int)(p->pos_y - p->plane_y * SPEED)][(int)p->pos_x] == FLOOR)
			p->pos_y -= p->plane_y * SPEED;
	}
	else if (keycode == KEY_D)
	{
		if (map[(int)p->pos_y][(int)(p->pos_x + p->plane_x * SPEED)] == FLOOR)
			p->pos_x += p->plane_x * SPEED;
		if (map[(int)(p->pos_y + p->plane_y * SPEED)][(int)p->pos_x] == FLOOR)
			p->pos_y += p->plane_y * SPEED;
	}
}

void	handle_look(int keycode, t_vars *vars)
{
	t_p		*p;
	float	old_dir_x;
	float	old_plane_x;

	p = &vars->p;
	if (keycode == KEY_RIGHT)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
		p->dir_y = old_dir_x * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-ROT_SPEED) - p->plane_y * sin(-ROT_SPEED);
		p->plane_y = old_plane_x * sin(-ROT_SPEED) + p->plane_y * cos(-ROT_SPEED);
	}
	else if (keycode == KEY_LEFT)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
		p->dir_y = old_dir_x * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
		p->plane_y = old_plane_x * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
	}
}
