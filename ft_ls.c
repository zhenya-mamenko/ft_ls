/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:31:45 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 23:23:44 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			g_exit_value = 0;

static DIR	*open_dir(char *name)
{
	DIR		*dirp;

	dirp = opendir(name);
	if (dirp == NULL)
		file_error(name);
	return (dirp);
}

static void	close_dir(DIR *dirp, char *name)
{
	if (closedir(dirp) != 0)
		file_error(name);
}

static void	ls_dir(DIR *dirp, size_t f, char *name)
{
	struct dirent	*ep;

	if (name != NULL)
		ft_printf("%s:\n", name);
	while ((ep = readdir(dirp)))
	{
		ft_printf("%s\n", ep->d_name);
	}
	if (f)
		;
}

static void	process_dir(char *name, size_t f, int show_name)
{
	DIR		*dirp;

	dirp = open_dir(name);
	if (dirp != NULL)
	{
		ls_dir(dirp, f, show_name == 1 ? name : NULL);
		close_dir(dirp, name);
	}
}

int			main(int ac, char **av)
{
	int		cnt;
	int		i;
	size_t	f;

	cnt = ac - 1;
	f = 0;
	if (cnt != 0)
		f = check_params(&cnt, av + 1);
	if (cnt == 0)
		process_dir(".", f, 0);
	else
	{
		i = -1;
		while (++i < cnt)
		{
			process_dir(av[ac - cnt + i], f, cnt == 1 ? 0 : 1);
			if (cnt != 1)
				ft_printf("\n");
		}
	}
	return (g_exit_value);
}
