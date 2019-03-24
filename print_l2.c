/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 13:30:19 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/24 14:22:51 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern size_t	g_flags;

void			colorize(t_file file)
{
	char	*s;

	s = "%s";
	if (S_ISLNK(file.st->st_mode))
		s = "%~fmagenta~%s%~-a~";
	else if (S_ISSOCK(file.st->st_mode))
		s = "%~fgreen~%s%~-a~";
	else if (file.st->st_mode & S_ISUID)
		s = "%~fblack;bred~%s%~-a~";
	else if (file.st->st_mode & S_ISGID)
		s = "%~fblack;bcyan~%s%~-a~";
	else if (file.st->st_mode & S_IFDIR)
		s = "%~s;flcyan~%s%~-a~";
	else if ((file.st->st_mode & S_IXUSR) || (file.st->st_mode & S_IXGRP)
		|| (file.st->st_mode & S_IXOTH))
		s = "%~fred~%s%~-a~";
	ft_printf((g_flags & 128) ? s : "%s", file.name);
	if ((g_flags & 4) && S_ISLNK(file.st->st_mode))
	{
		ft_printf(" -> ");
		s = readlnk(file.name);
		ft_printf(!s ? "" : s);
		ft_strdel(&s);
	}
	ft_printf("\n");
}

char			*readlnk(const char *filename)
{
	int		size;
	char	*buffer;
	int		n;

	size = 2000;
	buffer = (char *)malloc(sizeof(char) * (size + 1));
	ft_memset(buffer, 0, (size + 1));
	n = readlink(filename, buffer, size);
	if (n < 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
