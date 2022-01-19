/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:16:06 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/13 13:28:54 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map	*map)
{
	map->buffer = NULL;
	map->width = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->crgb = 0;
	map->frgb = 0;
	map->lines = 0;
	map->count = 0;
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	(void)argv;
	if (argc != 2)
		return (error_ret("Usage: ./cub3D map.cub\n", 1));
	if (check_format(argv[1]) != 0)
		return (1);
	init_map(&vars.map);
	if (first_read(argv[1], &vars.map) != 0)
		return (1);
	if (init_parse(&vars.map, argv[1]) != 0)
		return (1);
	mlx_main(&vars);
	return (0);
}
