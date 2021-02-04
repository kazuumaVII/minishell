/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_prsg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:24:49 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/22 13:59:42 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

int				env_size(char **list)
{
	int i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

int				ft_nb_pipe(char *str, int o)
{
	int			j;
	int			nb_pipe;
	int			quote;

	j = -1;
	nb_pipe = 0;
	quote = 0;
	while (str[++j])
	{
		if (str[j] == '"' && str[j - 1] != '\\')
			quote++;
		if (str[j] == '|' && (quote % 2) == 0 && str[j - 1] != '\\')
		{
			if (o == 1)
				return (j);
			nb_pipe++;
		}
	}
	if (o == 1)
		return (-1);
	return (nb_pipe);
}

int				parse_v1(char *str, int option, int pv)
{
	int			i;
	int			quote;

	i = 0;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == '"' && str[i - 1] != '\\')
			quote++;
		if (str[i] == ';' && (quote % 2) == 0 && str[i - 1] != '\\')
		{
			if (option == 1)
				return (i);
			pv++;
		}
	}
	if (option == 1)
		return (-1);
	return (pv);
}

char			**skip_last_arg_pv(char **tab, int pv)
{
	if (ft_strlen(tab[pv]) == 0)
	{
		free(tab[pv]);
		tab[pv] = NULL;
		return (tab);
	}
	return (tab);
}

char			**parse_v2(char *str)
{
	char		**tab;
	int			i;
	int			last_i;
	int			pv;

	last_i = 0;
	i = 0;
	pv = 0;
	if (!(tab = malloc(sizeof(char *) * (parse_v1(str, 0, pv) + 2))))
		return (NULL);
	pv = parse_v1(str, 0, pv);
	while (parse_v1(str + last_i, 1, pv) != -1)
	{
		tab[i] = ft_substr(str + last_i, 0, parse_v1(str + last_i, 1, pv));
		last_i += ft_strlen(tab[i]) + 1;
		i++;
	}
	tab[i] = ft_substr(str + last_i, 0, ft_strlen(str + last_i));
	tab[i + 1] = NULL;
	tab = skip_last_arg_pv(tab, pv);
	return (tab);
}
