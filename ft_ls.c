/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:31:45 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 21:51:02 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error(char *message, int and_exit, int and_free)
{
	ft_printf("%s: %s", NAME, message);
	if (and_free == 1)
		free(message);
	if (and_exit == 1)
		exit(1);
}

int		main(int ac, char **av)
{
	int		cnt;
	size_t	f;

	cnt = ac - 1;
	f = 0;
	if (cnt != 0)
		f = process_params(&cnt, av + 1);
}
