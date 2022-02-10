/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:16:06 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/02/10 16:33:20 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	if (argc != 2)
		return (error_ret("Usage: ./cub3D map.cub\n", 1));
	vars = (t_vars *)malloc(sizeof(t_vars));
	vars->map = (t_map *)malloc(sizeof(t_map));
	ft_putstr_fd("Parsing...\n", STDOUT_FILENO);
	if (check_format(argv[1]) != 0)
		return (1);
	init_map(vars->map);
	if (first_read(vars->map, argv[1]) != 0)
		return (1);
	if (init_parser(vars->map, argv[1]) != 0)
		return (1);
	vars->ray = (t_ray *)malloc(sizeof(t_ray));
	ft_putstr_fd("Starting minilibx...\n", STDOUT_FILENO);
	if (mlx_main(vars) != 0)
		return (EXIT_FAILURE);
	ft_putstr_fd("Quit\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
