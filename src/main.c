/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:16:06 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/31 18:37:40 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_utils vars;

	if (argc != 2)
		return (error_ret("Usage: ./cub3D map.cub\n", 1));
	if (check_format(argv[1]) != 0)
		return (1);
	if (first_read(argv[1], &vars) != 0)
		return (1);
}
