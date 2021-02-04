/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsg_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 15:59:49 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/22 16:50:02 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

char			*prsg_valu(char *str, t_shell *data)
{
	char		*valu;

	(void)*data;
	if (!(ft_strncmp(str, "$0", 3)))
		valu = ft_strdup("bash");
	else if (!(ft_strncmp(str, "$0", 3)))
		valu = ft_strdup("bash");
	else if (!ft_strncmp(str, "00", 3))
		valu = ft_strdup("");
	else if (!ft_strncmp(str, "_=", 3))
		valu = ft_strdup(g_last);
	else if (str[0] == '?' && ft_strlen(str) == 2)
		valu = ft_itoa(g_return_valu);
	else
		valu = ft_strdup("");
	return (valu);
}

char			*var_name_prsg(char *str)
{
	int			i;
	char		*name;

	i = -1;
	if (str[0] == '?')
		return (ft_strdup("?="));
	if (str[0] == '0')
		return (ft_strdup("$0"));
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (ft_strdup("00"));
	while (str[++i])
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
	if (!(name = malloc(sizeof(char) * (i + 2))))
		return (NULL);
	name[i + 1] = '\0';
	name[i] = '=';
	while (i-- > 0)
		name[i] = str[i];
	return (name);
}

char			*parse_var(char *str, t_shell *data)
{
	int			i;

	i = -1;
	while (str[++i])
	{
		if (is_correct(str, i))
		{
			if (!(str = check_validity(str, i, data)))
				return (NULL);
			i = -1;
		}
	}
	return (str);
}
