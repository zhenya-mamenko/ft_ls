/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:34:48 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/24 15:22:53 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/types.h>
# include <sys/acl.h>
# include "libft/libft.h"

# define NAME		"ft_ls"

typedef struct		s_param
{
	char			param;
	size_t			flag;
}					t_param;

typedef struct		s_file
{
	char			*name;
	char			*path;
	struct stat		*st;
	size_t			len;
	struct s_file	*next;
}					t_file;

typedef struct		s_dir
{
	char			*path;
	quad_t			blocks_cnt;
	quad_t			blocks_cnt2;
	size_t			files_cnt;
	size_t			files_cnt2;
	size_t			max_len;
	size_t			max_nlink;
	size_t			max_user;
	size_t			max_group;
	size_t			max_size;
	struct stat		*st;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_udata
{
	struct passwd	*pwd;
	struct group	*grp;
	char			*dt;
}					t_udata;

static int			g_param_count = 8;
static t_param		g_params[] =
{
	{ 'G', 128 },
	{ 'R', 2 },
	{ 'T', 256 },
	{ 'a', 4 },
	{ 'l', 8 },
	{ 'r', 16 },
	{ 't', 32 },
	{ '1', 64 }
};

void				error(char *message, int and_exit, int and_free);
void				file_error(char *file_name);
size_t				check_params(int *ac, char **av);
t_file				*process_dir(char *name, size_t f, t_file **root);
t_file				*create_node(t_file *prev, char *name, char *path,
						struct stat *st);
void				clear_list(t_file *root);
t_dir				*get_dir(t_dir **root, char *path);
void				set_dir_data(t_dir **root, t_file *file, size_t f);
void				clear_dir(t_dir *root);
void				print_data(size_t f, int cnt);
void				print_l(t_file *a, t_file *n, int ix);
void				sort_array(t_file *a, size_t f);
void				colorize(t_file file);

#endif
