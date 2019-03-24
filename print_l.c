/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 09:44:46 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/24 14:50:04 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int		g_file_count;
extern t_dir	*g_dir;
extern size_t	g_flags;

static char	get_mode(unsigned short st_mode)
{
	char	mode;

	if (S_ISREG(st_mode))
		mode = '-';
	else if (S_ISDIR(st_mode))
		mode = 'd';
	else if (S_ISCHR(st_mode))
		mode = 'c';
	else if (S_ISBLK(st_mode))
		mode = 'b';
	else if (S_ISFIFO(st_mode))
		mode = 'p';
	else if (S_ISLNK(st_mode))
		mode = 'l';
	else if (S_ISSOCK(st_mode))
		mode = 's';
	else
		mode = '?';
	return (mode);
}

static char	*get_perm(unsigned short st_mode, char *p)
{
	p[0] = (st_mode & S_IRUSR) ? 'r' : '-';
	p[1] = (st_mode & S_IWUSR) ? 'w' : '-';
	if (st_mode & S_ISUID)
		p[2] = (st_mode & S_IXUSR) ? 's' : 'S';
	else
		p[2] = (st_mode & S_IXUSR) ? 'x' : '-';
	p[3] = (st_mode & S_IRGRP) ? 'r' : '-';
	p[4] = (st_mode & S_IWGRP) ? 'w' : '-';
	if (st_mode & S_ISGID)
		p[5] = (st_mode & S_IXGRP) ? 's' : 'S';
	else
		p[5] = (st_mode & S_IXGRP) ? 'x' : '-';
	p[6] = (st_mode & S_IROTH) ? 'r' : '-';
	p[7] = (st_mode & S_IWOTH) ? 'w' : '-';
	if (st_mode & S_ISVTX)
		p[8] = (st_mode & S_IXOTH) ? 't' : 'T';
	else
		p[8] = (st_mode & S_IXOTH) ? 'x' : '-';
	p[9] = 0;
	return (p);
}

static void	get_udata(struct stat *st, t_udata *data)
{
	struct timespec	ts;

	ts = st->st_ctimespec;
	(*data).dt = ctime(&ts.tv_sec);
	(*data).grp = getgrgid(st->st_gid);
	(*data).pwd = getpwuid(st->st_uid);
}

static char	get_x_attr(char *name)
{
	acl_t		acl;
	acl_entry_t	dummy;
	ssize_t		xattr;
	char		a;

	acl = acl_get_link_np(name, ACL_TYPE_EXTENDED);
	if (acl &&
		acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(name, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;

	if (xattr > 0)
		a = '@';
	else if (acl != NULL)
		a = '+';
	else
		a = ' ';
	return (a);
}

void		print_l(t_file *a, t_file *n, int ix)
{
	t_dir		*dir;
	size_t		k;
	char		*s;
	t_udata		d;
	char		p[10];

	dir = get_dir(&g_dir, n->path);
	k = -1;
	while (++k < dir->files_cnt)
		if ((a[ix + k]).name[0] != '.' || (g_flags & 4))
		{
			s = ft_ssprintf("%%c%%s%%c %%%dd %%- %ds  %%- %ds  %%%dd ",
				dir->max_nlink, dir->max_user, dir->max_group, dir->max_size);
			get_udata(a[ix + k].st, &d);
			get_perm(a[ix + k].st->st_mode, p);
			ft_printf(s, get_mode(a[ix + k].st->st_mode), p,
				get_x_attr(n->name),
				a[ix + k].st->st_nlink, !d.pwd ? "" : d.pwd->pw_name,
				!d.grp ? "" : d.grp->gr_name, a[ix + k].st->st_size);
			ft_strdel(&s);
			ft_printf("%s ", (g_flags & 256) ? (s = ft_strsub(d.dt, 0, 24)) :
				(s = ft_strsub(d.dt, 4, 12)));
			colorize(a[ix + k]);
			ft_strdel(&s);
		}
}
