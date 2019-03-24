/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:49:55 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 22:31:57 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	error_in_pparams(char *p)
{
	char	*s;
	int		i;

	s = malloc(sizeof(char) * (g_param_count + 1));
	i = 0;
	while (i < g_param_count)
	{
		s[i] = g_params[i].param;
		i++;
	}
	s[g_param_count] = '\0';
	error(ft_ssprintf("illegal option -- %c\n", p[0]), 0, 1);
	ft_printf("usage: %s [-%s] [file ...]\n", NAME, s);
	ft_strdel(&s);
	exit(1);
	return (-1);
}

static int	check_partial_params(char **av, int *i)
{
	int		j;
	size_t	k;
	int		f;
	char	*p;

	f = 0;
	j = -1;
	p = ft_strsub(av[*i], 1, ft_strlen(av[*i]) - 1);
	while (++j < g_param_count)
		if ((k = ft_strchri(p, g_params[j].param)) != -1)
		{
			ft_strcpy(p + k, p + k + 1);
			f |= g_params[j].flag;
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
		else if ((j = check_partial_params(av, &i)) == -1)
			return (1);
		f |= j;
	}
	*ac -= i;
	return (f);
}
