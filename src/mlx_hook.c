/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:55:56 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/19 09:04:46 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_vars *vars)
{
	free_all(vars);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	//printf("key: %d\n", keycode);
	if (keycode == KEY_ESC)
		return (0);//close_win(vars);
	else if (keycode == KEY_W || keycode == KEY_S)
		handle_move(keycode, vars);
	else if (keycode == KEY_A || keycode == KEY_D)
		handle_sidemove(keycode, vars);
	else if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		handle_look(keycode, vars);
	else if (keycode == KEY_E)
		handle_door(vars);
	return (0);
}
