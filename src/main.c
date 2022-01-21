/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:16:06 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/19 10:36:35 by dpoveda-         ###   ########.fr       */
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
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	(void)argv;
	if (argc != 2)
		return (error_ret("Usage: ./cub3D map.cub\n", 1));
	printf("Parsing...\n");
	//if (check_format(argv[1]) != 0)
	//	return (1);
	//init_map(&vars.map);
	//if (first_read(argv[1], &vars.map) != 0)
	//	return (1);
	/*vars.map.height = 5;
	vars.map.width = 8;
	vars.map.map = (char **)malloc(sizeof(char *) * 6);
	vars.map.map[0] = ft_strdup("1111 111");
	vars.map.map[1] = ft_strdup(" 1011101");
	vars.map.map[2] = ft_strdup(" 1010101");
	vars.map.map[3] = ft_strdup(" 1011101");
	vars.map.map[4] = ft_strdup("11111111");
	vars.map.map[5] = NULL;*/
	//
	vars.p.pos_x = 9;
	vars.p.pos_y = 3;
	vars.p.dir_x = -1;
	vars.p.dir_y = 0;
	vars.p.plane_x = 0;
	vars.p.plane_y = 0.66;
	vars.map.height = 10;
	vars.map.width = 15;
	//vars.map.frgb = 0xFFFF0000;
	//vars.map.frgb = 0xFF0000FF;
	vars.map.map = (char **)malloc(sizeof(char *) * 11);
	vars.map.map[0] = ft_strdup("1111 1111111111");
	vars.map.map[1] = ft_strdup(" 10111000000001");
	vars.map.map[2] = ft_strdup(" 10101000000001");
	vars.map.map[3] = ft_strdup(" 10111000000001");
	vars.map.map[4] = ft_strdup("111111100000001");
	vars.map.map[5] = ft_strdup("111111100000001");
	vars.map.map[6] = ft_strdup("101011100000001");
	vars.map.map[7] = ft_strdup("111111100000111");
	vars.map.map[8] = ft_strdup("1010111111111 1");
	vars.map.map[9] = ft_strdup("1111111       1");
	vars.map.map[10] = NULL;
	//
	printf("Starting minilibx...\n");
	mlx_main(&vars);
	return (0);
}
