/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:39:58 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/08 13:39:59 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir(t_p *p, int dir_x, int dir_y)
{
	p->dir_x = dir_x;
	p->dir_y = dir_y;
}

static void	set_plane(t_p *p, float plane_x, float plane_y)
{
	p->plane_x = plane_x;
	p->plane_y = plane_y;
}

int	player_init(t_vars *vars)
{
	if (vars->map->start_orientation == 'N')
	{
		set_dir(&vars->p, 0, -1);
		set_plane(&vars->p, -0.66, 0);
	}
	else if (vars->map->start_orientation == 'S')
	{
		set_dir(&vars->p, 0, 1);
		set_plane(&vars->p, 0.66, 0.0);
	}
	else if (vars->map->start_orientation == 'W')
	{
		set_dir(&vars->p, -1, 0);
		set_plane(&vars->p, 0.0, 0.66);
	}
	else if (vars->map->start_orientation == 'E')
	{
		set_dir(&vars->p, 1, 0);
		set_plane(&vars->p, 0.0, -0.66);
	}
	vars->p.pos_x = (float)vars->map->p_pos[0] + 0.5;
	vars->p.pos_y = (float)vars->map->p_pos[1] + 0.5;
	return (0);
}
