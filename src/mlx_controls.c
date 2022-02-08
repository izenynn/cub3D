/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:46:41 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/08 13:46:43 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_move(int keycode, t_vars *vars, float speed)
{
	t_p		*p;
	char	**m;

	p = &vars->p;
	m = vars->map->map;
	if (keycode == KEY_W)
	{
		if (m[(int)p->pos_y][(int)(p->pos_x + p->dir_x * speed)] == DOOR_OPEN
			|| m[(int)p->pos_y][(int)(p->pos_x + p->dir_x * speed)] == FLOOR)
			p->pos_x += p->dir_x * speed;
		if (m[(int)(p->pos_y + p->dir_y * speed)][(int)p->pos_x] == DOOR_OPEN
			|| m[(int)(p->pos_y + p->dir_y * speed)][(int)p->pos_x] == FLOOR)
			p->pos_y += p->dir_y * speed;
	}
	else if (keycode == KEY_S)
	{
		if (m[(int)p->pos_y][(int)(p->pos_x - p->dir_x * speed)] == DOOR_OPEN
			|| m[(int)p->pos_y][(int)(p->pos_x - p->dir_x * speed)] == FLOOR)
			p->pos_x -= p->dir_x * speed;
		if (m[(int)(p->pos_y - p->dir_y * speed)][(int)p->pos_x] == DOOR_OPEN
			|| m[(int)(p->pos_y - p->dir_y * speed)][(int)p->pos_x] == FLOOR)
			p->pos_y -= p->dir_y * speed;
	}
}

static void	handle_sidemove(int keycode, t_vars *vars, float speed)
{
	t_p		*p;
	char	**m;

	p = &vars->p;
	m = vars->map->map;
	if (keycode == KEY_D)
	{
		if (m[(int)p->pos_y][(int)(p->pos_x - p->plane_x * speed)] == DOOR_OPEN
			|| m[(int)p->pos_y][(int)(p->pos_x - p->plane_x * speed)] == FLOOR)
			p->pos_x -= p->plane_x * speed;
		if (m[(int)(p->pos_y - p->plane_y * speed)][(int)p->pos_x] == DOOR_OPEN
			|| m[(int)(p->pos_y - p->plane_y * speed)][(int)p->pos_x] == FLOOR)
			p->pos_y -= p->plane_y * speed;
	}
	else if (keycode == KEY_A)
	{
		if (m[(int)p->pos_y][(int)(p->pos_x + p->plane_x * speed)] == DOOR_OPEN
			|| m[(int)p->pos_y][(int)(p->pos_x + p->plane_x * speed)] == FLOOR)
			p->pos_x += p->plane_x * speed;
		if (m[(int)(p->pos_y + p->plane_y * speed)][(int)p->pos_x] == DOOR_OPEN
			|| m[(int)(p->pos_y + p->plane_y * speed)][(int)p->pos_x] == FLOOR)
			p->pos_y += p->plane_y * speed;
	}
}

static void	handle_look(int keycode, t_vars *vars, float speed)
{
	t_p		*p;
	float	old_dir_x;
	float	old_plane_x;

	p = &vars->p;
	if (keycode == KEY_LEFT)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-speed) - p->dir_y * sin(-speed);
		p->dir_y = old_dir_x * sin(-speed) + p->dir_y * cos(-speed);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-speed) - p->plane_y * sin(-speed);
		p->plane_y = old_plane_x * sin(-speed) + p->plane_y * cos(-speed);
	}
	else if (keycode == KEY_RIGHT)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(speed) - p->dir_y * sin(speed);
		p->dir_y = old_dir_x * sin(speed) + p->dir_y * cos(speed);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(speed) - p->plane_y * sin(speed);
		p->plane_y = old_plane_x * sin(speed) + p->plane_y * cos(speed);
	}
}

void	handle_keys(t_vars *vars)
{
	if (vars->keys.w != vars->keys.s)
	{
		if (vars->keys.w == TRUE)
			handle_move(KEY_W, vars, DEFAULT_SPEED);
		else if (vars->keys.s == TRUE)
			handle_move(KEY_S, vars, DEFAULT_SPEED);
	}
	if (vars->keys.a != vars->keys.d)
	{
		if (vars->keys.a == TRUE)
			handle_sidemove(KEY_A, vars, DEFAULT_SPEED);
		else if (vars->keys.d == TRUE)
			handle_sidemove(KEY_D, vars, DEFAULT_SPEED);
	}
	if (vars->keys.right_arrow != vars->keys.left_arrow)
	{
		if (vars->keys.right_arrow == TRUE)
			handle_look(KEY_RIGHT, vars, DEFAULT_ROT_SPEED);
		else if (vars->keys.left_arrow == TRUE)
			handle_look(KEY_LEFT, vars, DEFAULT_ROT_SPEED);
	}
}

void	handle_door(t_vars *vars)
{
	t_p		*p;
	char	**m;
	int		door_hit[2];

	p = &vars->p;
	m = vars->map->map;
	door_hit[X] = vars->door_hit[X];
	door_hit[Y] = vars->door_hit[Y];
	if (door_hit[X] == -1 || door_hit[Y] == -1)
		return ;
	if (m[door_hit[Y]][door_hit[X]] == DOOR_CLOSE
		&& ((int)p->pos_x != door_hit[X] || (int)p->pos_y != door_hit[Y]))
		m[door_hit[Y]][door_hit[X]] = DOOR_OPEN;
	else if (m[door_hit[Y]][door_hit[X]] == DOOR_OPEN
		&& ((int)p->pos_x != door_hit[X] || (int)p->pos_y != door_hit[Y]))
		m[door_hit[Y]][door_hit[X]] = DOOR_CLOSE;
}
