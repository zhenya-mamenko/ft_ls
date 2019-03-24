/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 09:05:09 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/24 10:15:05 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int		g_file_count;
extern t_dir	*g_dir;
extern t_file	*g_root;
extern size_t	g_flags;

static int		cmp_dir(t_file *f1, t_file *f2)
{
	int			res;

	if ((g_flags & 32) &&
		(res = get_dir(&g_dir, f1->path)->st->st_ctimespec.tv_sec -
			get_dir(&g_dir, f2->path)->st->st_ctimespec.tv_sec) != 0)
		return (-res);
	return (ft_strcmp(f1->path, f2->path));
}

static int		fn_cmp(const void *a, const void *b)
{
	t_file		*f1;
	t_file		*f2;
	int			res;

	f1 = (t_file *)a;
	f2 = (t_file *)b;
	if ((res = cmp_dir(f1, f2)) != 0)
		return (res);
	if ((g_flags & 32) &&
		(res = f1->st->st_ctimespec.tv_sec - f2->st->st_ctimespec.tv_sec) != 0)
		return (-res);
	res = ft_strcmp(f1->name, f2->name);
	return (res);
}

void			sort_array(t_file *a, size_t f)
{
	g_flags = f;
	ft_qsort(a, g_file_count, sizeof(t_file), fn_cmp);
}
