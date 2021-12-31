/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:15:51 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/31 18:39:02 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

/* exit printint perror */
void	perror_exit(const char *s)
{
	if (s == NULL)
		perror("minishell");
	else
		perror(s);
	exit(EXIT_FAILURE);
}

/* return with custom error code */
int	perror_ret(const char *s, int ret_code)
{
	if (s == NULL)
		perror("minishell");
	else
		perror(s);
	return (ret_code);
}

/* return with custom error code */
int	error_ret(const char *s, int ret_code)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	return (ret_code);
}
