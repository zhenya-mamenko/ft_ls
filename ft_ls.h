/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:34:48 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 21:49:02 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include "libft/libft.h"

# define NAME		"ft_ls"

typedef struct		s_param
{
	char			*param;
	char			*description;
	size_t			flag;
}					t_param;

static int			g_param_count = 5;
static t_param		g_params[] =
{
	{
		"p",
		"Echo stdin to stdout and append the checksum to stdout.",
		1024
	},
};

void				error(char *message, int and_exit, int and_free);

#endif
