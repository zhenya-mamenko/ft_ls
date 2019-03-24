/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 22:54:33 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 23:15:29 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int		g_exit_value;

void			error(char *message, int and_exit, int and_free)
{
	ft_printf("%s: %s", NAME, message);
	if (and_free == 1)
		free(message);
	if (and_exit == 1)
		exit(1);
}

void			file_error(char *file_name)
{
	extern int	errno;

	ft_printf("%s: %s: %s\n", NAME, file_name, strerror(errno));
	g_exit_value = 1;
}
