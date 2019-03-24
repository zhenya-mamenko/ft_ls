/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:31:45 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/24 12:52:11 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			g_exit_value = 0;
int			g_file_count = 0;
t_file		*g_root = NULL;
t_dir		*g_dir = NULL;

static void	ls_dir(DIR *dirp, size_t f, char *path, t_file **node)
{
	struct dirent	*ep;
	char			*p;
	struct stat		st;

	while ((ep = readdir(dirp)))
	{
		g_file_count++;
		p = ft_strjoin(path, "/");
		ft_strsetdel(&p, ft_strjoin(p, ep->d_name));
		lstat(p, &st);
		(*node)->next = create_node(*node, ep->d_name, path, &st);
		*node = (*node)->next;
		if ((st.st_mode & S_IFDIR) && (f & 2) &&
			!(ft_strcmp(ep->d_name, ".") == 0 ||
			ft_strcmp(ep->d_name, "..") == 0))
			process_dir(p, f, node);
		ft_strdel(&p);
	}
}

t_file		*process_dir(char *name, size_t f, t_file **root)
{
	DIR				*dirp;
	struct stat		st;
	int				res;

	if ((res = lstat(name == NULL ? "." : name, &st)) != 0)
		file_error(name);
	else if (!(st.st_mode & S_IFDIR))
	{
		create_node(*root, name, ft_strdup(""), &st);
		*root = (*root)->next;
		g_file_count++;
	}
	else
	{
		dirp = opendir(name == NULL ? "." : name);
		if (dirp != NULL)
		{
			ls_dir(dirp, f, name == NULL ? "." : name, root);
			if (closedir(dirp) != 0)
				file_error(name == NULL ? "." : name);
		}
		else
			file_error(name == NULL ? "." : name);
	}
	return (*root);
}

int			main(int ac, char **av)
{
	int			cnt;
	int			i;
	size_t		f;
	t_file		*node;

	g_root = create_node(NULL, NULL, NULL, NULL);
	node = g_root;
	cnt = ac - 1;
	f = 0;
	if (cnt != 0)
		f = check_params(&cnt, av + 1);
	if (cnt == 0)
		process_dir(NULL, f, &node);
	else
	{
		i = -1;
		while (++i < cnt)
			process_dir(av[ac - cnt + i], f, &node);
	}
	print_data(f, cnt);
	clear_list(g_root);
	clear_dir(g_dir);
	return (g_exit_value);
}
