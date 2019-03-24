/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:34:48 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 22:59:27 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <dirent.h>
# include <sys/errno.h>
# include "libft/libft.h"

# define NAME		"ft_ls"

typedef struct		s_param
{
	char			param;
	size_t			flag;
}					t_param;

static int			g_param_count = 5;
static t_param		g_params[] =
{
	{ 'R', 2 },
	{ 'a', 4 },
	{ 'l', 8 },
	{ 'r', 16 },
	{ 't', 32 }
};

void				error(char *message, int and_exit, int and_free);
void				file_error(char *file_name);
size_t				check_params(int *ac, char **av);

#endif
