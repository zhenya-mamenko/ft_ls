/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 03:24:00 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/24 15:06:49 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int		g_file_count;
extern t_dir	*g_dir;
extern t_file	*g_root;
size_t			g_flags;

static void		get_rc(t_dir *dir, size_t *rows, size_t *cols)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if ((*cols = w.ws_col / (dir->max_len + 1)) == 0)
		*cols = 1;
	*rows = (dir->files_cnt2 / *cols) +
		((dir->files_cnt2 % *cols) == 0 ? 0 : 1);
	if ((g_flags & 64) || (*rows > w.ws_row))
	{
		*rows = dir->files_cnt2;
		*cols = 1;
	}
}

static void		print_columns(t_file *a, t_file *n, int ix)
{
	t_dir			*dir;
	size_t			cols;
	size_t			rows;
	size_t			i;
	size_t			k;

	dir = get_dir(&g_dir, n->path);
	get_rc(dir, &rows, &cols);
	i = 0;
	k = -1;
	while (++k < dir->files_cnt && i < dir->files_cnt2)
		if ((a[ix + k]).name[0] != '.' || (g_flags & 4))
		{
			if (i / rows != 0)
				ft_printf("\x1b[%dC", (dir->max_len + 1) * (i / rows));
			colorize(a[ix + k]);
			if ((++i) % rows == 0 && cols != 1)
				ft_printf("\x1b[%dA", rows);
		}
	i = i % rows == 0 ? 0 : i;
	while (i == 0 || (i % rows != 0 && cols != 1))
		ft_printf("\n", i++);
}

void			print_dir(t_file *a, t_file *n, int *ix, int cnt)
{
	t_dir			*dir;
	char			*s;

	dir = get_dir(&g_dir, n->path);
	if (!(cnt < 2 && *ix == 0))
		ft_printf("%s%s%s", (*ix != 0 ? "\n" : ""), ft_strlen(n->path) \
			== 0 ? "" : n->path, ft_strlen(n->path) == 0 ? "" : ":\n");
	if ((g_flags & 8) && !(g_flags & 64))
	{
		s = ft_ssprintf("total %u\n",
			dir->blocks_cnt + (g_flags & 4 ? dir->blocks_cnt2 : 0));
		if (ft_strlen(n->path) != 0)
			ft_printf("%s", s);
		print_l(a, n, *ix);
	}
	else
		print_columns(a, n, *ix);
	(*ix) += dir->files_cnt - 1;
}

void			print_data(size_t f, int cnt)
{
	t_file		*a;
	t_file		*node;
	int			i;
	char		*p;

	if ((a = malloc(sizeof(t_file) * g_file_count)) == NULL)
		error("Error: can't allocate memmory for array", 1, 0);
	node = g_root->next;
	i = 0;
	while (node)
	{
		ft_memcpy(&a[i++], node, sizeof(t_file));
		set_dir_data(&g_dir, node, f);
		node = node->next;
	}
	sort_array(a, f);
	f = 0;
	p = NULL;
	i = -1;
	while (++i < g_file_count)
		if (ft_strcmp(p, a[i].path) != 0)
			if (ft_strstri((p = a[i].path), "/.") == -1 || (f & 4))
				print_dir(a, &a[i], &i, cnt);
	ft_memdel((void **)&a);
}
