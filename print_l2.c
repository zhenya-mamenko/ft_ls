/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 13:30:19 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/24 15:39:58 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern size_t	g_flags;

static void		get_color_string(char **s, t_file *file)
{
	*s = "%s";
	if (S_ISLNK(file->st->st_mode))
		*s = "%~fmagenta~%s%~-a~";
	else if (S_ISSOCK(file->st->st_mode))
		*s = "%~fgreen~%s%~-a~";
	else if (file->st->st_mode & S_ISUID)
		*s = "%~fblack;bred~%s%~-a~";
	else if (file->st->st_mode & S_ISGID)
		*s = "%~fblack;bcyan~%s%~-a~";
	else if (file->st->st_mode & S_IFDIR)
		*s = "%~s;flcyan~%s%~-a~";
	else if ((file->st->st_mode & S_IXUSR) || (file->st->st_mode & S_IXGRP)
		|| (file->st->st_mode & S_IXOTH))
		*s = "%~fred~%s%~-a~";
}

static char		*readlnk(const char *filename)
{
	int		size;
	int		n;
	char	*buf;

	size = 2000;
	buf = malloc(size);
	if (buf)
	{
		n = readlink(filename, buf, size - 1);
		if (n > -1)
			buf[n] = '\0';
	}
	return (buf);
}

void			colorize(t_file file)
{
	char	s[2000];
	char	*ss;

	ss = s;
	get_color_string(&ss, &file);
	ft_printf((g_flags & 128) ? ss : "%s", file.name);
	if ((g_flags & 4) && S_ISLNK(file.st->st_mode))
	{
		ft_printf(" -> ");
		ft_memset(s, 0, 2000);
		ft_strcpy(s, file.path);
		s[ft_strlen(file.path)] = '/';
		ft_strcpy(s + ft_strlen(file.path) + 1, file.name);
		ss = readlnk(s);
		ft_printf(ft_strlen(ss) == 0 ? "" : ss);
		ft_strdel(&ss);
	}
	ft_printf("\n");
}
