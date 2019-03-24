/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:52:56 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/24 02:36:45 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*create_node(t_file *prev, char *name, char *path, struct stat *st)
{
	t_file		*node;

	node = malloc(sizeof(t_file));
	if (node == NULL)
		error("Error: can't allocate memmory for t_file", 1, 0);
	node->name = name == NULL ? NULL : ft_strdup(name);
	node->path = path == NULL ? NULL : ft_strdup(path);
	node->len = ft_strlen(name);
	node->st = NULL;
	if (st != NULL)
	{
		node->st = malloc(sizeof(struct stat));
		if (node->st == NULL)
		{
			free(node);
			error("Error: can't allocate memmory for struct stat", 1, 0);
		}
		ft_memcpy(node->st, st, sizeof(struct stat));
	}
	node->next = NULL;
	if (prev != NULL)
		prev->next = node;
	return (node);
}

void		clear_list(t_file *root)
{
	t_file	*node;

	while (root)
	{
		node = root;
		root = root->next;
		ft_memdel((void **)&(node->st));
		ft_memdel((void **)&(node->path));
		ft_memdel((void **)&(node->name));
		ft_memdel((void **)&(node));
	}
}
