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

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	(void)argv;
	if (argc != 2)
		return (error_ret("Usage: ./cub3D map.cub\n", 1));
	vars = (t_vars *)malloc(sizeof(t_vars));
	write(STDOUT_FILENO, "Parsing...\n", 11);
	if (check_format(argv[1]) != 0)
		return (1);
	init_map(&vars->map);
	if (first_read(argv[1], &vars->map) != 0)
		return (1);
	if (init_parser(&vars->map, argv[1]) != 0)
		return (1);
	write(STDOUT_FILENO, "Starting minilibx\n", 18);
	// ============== HARDCODEADA ================
	vars->map.map = (char **)malloc(sizeof(char *) * 15);
	vars->map.map[0]  = ft_strdup("        1111111111111111111111111");
	vars->map.map[1]  = ft_strdup("        1000000000110000000000001");
	vars->map.map[2]  = ft_strdup("        1011000001110000000000001");
	vars->map.map[3]  = ft_strdup("        1001000000000000000000001");
	vars->map.map[4]  = ft_strdup("111111111011000001110000000000001");
	vars->map.map[5]  = ft_strdup("100000000011000001110111100000111");
	vars->map.map[6]  = ft_strdup("1111011111111101110000001110111");
	vars->map.map[7]  = ft_strdup("111101111111110111010100101O101");
	vars->map.map[8]  = ft_strdup("1100000011010101110000001000001");
	vars->map.map[9]  = ft_strdup("1000000000000000110000001000111");
	vars->map.map[10] = ft_strdup("1000000000000000110101001000O01");
	vars->map.map[11] = ft_strdup("110000011101010111110110100011111");
	vars->map.map[12] = ft_strdup("11110111 1110101 1011110C000001");
	vars->map.map[13] = ft_strdup("11111111 1111111 11111111111111");
	vars->map.map[14] = NULL;
	vars->map.door = ft_strdup("./textures/door.xpm");
	vars->map.sprite = ft_strdup("./textures/barrel.xpm");
	vars->sprites = (t_sprite **)malloc(sizeof(t_sprite *) * 3);
	vars->sprites[0] = (t_sprite *)malloc(sizeof(t_sprite));
	vars->sprites[0]->x = 9;
	vars->sprites[0]->y = 9;
	vars->sprites[1] = (t_sprite *)malloc(sizeof(t_sprite));
	vars->sprites[1]->x = 7;
	vars->sprites[1]->y = 7;
	vars->sprites[2] = NULL;
	// ============= NO MAS HARDCODEADA ==============
	if (mlx_main(vars) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
