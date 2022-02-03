/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:15:51 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/13 13:28:02 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* print perror and exit */
void	perror_exit(const char *s)
{
	if (s != NULL)
		perror(s);
	else if (NAME != NULL)
		perror(NAME);
	else
		perror("error");
	exit(EXIT_FAILURE);
}

/* return perror with custom error code */
int	perror_ret(const char *s, int ret_code)
{
	if (s != NULL)
		perror(s);
	else if (NAME != NULL)
		perror(NAME);
	else
		perror("error");
	return (ret_code);
}

/* return custom error with custom error code */
int	error_ret(const char *s, int ret_code)
{
	if (NAME != NULL)
	{
		write(STDERR_FILENO, NAME, ft_strlen(NAME));
	}
	else
		write(STDERR_FILENO, "error", 5);
	write(STDERR_FILENO, ": ", 2);
	if (s)
		write(STDERR_FILENO, s, ft_strlen(s));
	return (ret_code);
}
