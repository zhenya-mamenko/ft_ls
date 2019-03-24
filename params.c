/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:49:55 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 21:48:06 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	error_in_pparams(char *p)
{
	error(ft_ssprintf("illegal option(s) -- %s\n", p), 0, 1);
	ft_printf("usage: %s [-%s] [file ...]\n", NAME, "Ralrt");
	exit(1);
	return (-1);
}

static int	check_partial_params(char **av, int *i, int ac)
{
	int		j;
	size_t	k;
	int		f;
	char	*p;
	t_param	pm;

	f = 0;
	j = -1;
	p = ft_strsub(av[*i], 1, ft_strlen(av[*i]) - 1);
	while (++j < g_param_count)
		if ((k = ft_strstri(p, g_params[j].param)) != -1)
		{
			ft_strcpy(p + k, p + k + ft_strlen(pm.param));
			f |= pm.flag;
		}
	return (ft_strlen(p) == 0 ? f : error_in_pparams(p));
}

size_t		check_params(int *ac, char **av)
{
	int		i;
	int		j;
	size_t	f;

	f = 0;
	i = -1;
	while (++i < *ac)
	{
		if (av[i][0] != '-')
			break ;
		else if ((j = check_partial_params(av, &i, *ac)) == -1)
			return (1);
		f |= j;
	}
	*ac -= i;
	return (f);
}
