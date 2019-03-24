/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 02:59:37 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/24 11:37:20 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_dir	*create_dir(t_dir **root, char *path)
{
	t_dir	*dir;

	dir = malloc(sizeof(t_dir));
	if (dir == NULL)
		error("Error: can't allocate memmory for t_dir", 1, 0);
	dir->blocks_cnt = 0;
	dir->blocks_cnt2 = 0;
	dir->files_cnt = 0;
	dir->files_cnt2 = 0;
	dir->max_len = 0;
	dir->max_nlink = 0;
	dir->max_user = 0;
	dir->max_group = 0;
	dir->max_size = 0;
	dir->path = ft_strdup(path);
	dir->next = NULL;
	dir->st = malloc(sizeof(struct stat));
	if (dir->st == NULL)
		error("Error: can't allocate memmory for struct stat", 1, 0);
	if (*root != NULL)
		(*root)->next = dir;
	else
		*root = dir;
	return (dir);
}

t_dir			*get_dir(t_dir **root, char *path)
{
	t_dir	*dir;
	t_dir	*p;

	dir = *root;
	while (dir)
	{
		if (ft_strcmp(dir->path, path) == 0)
			break ;
		p = dir;
		dir = dir->next;
	}
	if (dir == NULL)
		dir = create_dir(*root != NULL ? &p : root, path);
	return (dir);
}

static void		check_max(t_dir *dir, t_file *file)
{
	size_t			len;
	struct passwd	*pwd;
	struct group	*grp;

	len = ft_strlen(file->name);
	dir->max_len = dir->max_len < len ? len : dir->max_len;
	len = ft_strlen(ft_itoa(file->st->st_nlink));
	dir->max_nlink = dir->max_nlink < len ? len : dir->max_nlink;
	len = 0;
	if ((pwd = getpwuid(file->st->st_uid)) != NULL)
		len = ft_strlen(pwd->pw_name);
	dir->max_user = dir->max_user < len ? len : dir->max_user;
	len = 0;
	if ((grp = getgrgid(file->st->st_gid)) != NULL)
		len = ft_strlen(grp->gr_name);
	dir->max_group = dir->max_group < len ? len : dir->max_group;
	len = ft_strlen(ft_itoa(file->st->st_size));
	dir->max_size = dir->max_size < len ? len : dir->max_size;
}

void			set_dir_data(t_dir **root, t_file *file, size_t f)
{
	t_dir	*dir;

	dir = get_dir(root, file->path);
	if (ft_strcmp(file->name, ".") == 0)
		ft_memcpy(dir->st, file->st, sizeof(struct stat));
	dir->files_cnt++;
	if (file->name[0] != '.' || (f & 4))
	{
		dir->files_cnt2++;
		dir->blocks_cnt += file->st->st_blocks;
		check_max(dir, file);
	}
	else
		dir->blocks_cnt2 += file->st->st_blocks;
}

void			clear_dir(t_dir *root)
{
	t_dir	*node;

	while (root)
	{
		node = root;
		root = root->next;
		ft_memdel((void **)&(node->st));
		ft_memdel((void **)&(node->path));
		ft_memdel((void **)&(node));
	}
}
