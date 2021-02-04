/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsg_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:01:40 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/20 17:07:04 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

void			clean_array(char **array)
{
	int			i;

	i = -1;
	if (array)
	{
		while (array[++i])
			free(array[i]);
		free(array);
	}
}

void			free_handle_arg(char **str, int *i, int *nb_arg)
{
	free(*str);
	*str = NULL;
	*i = *i - 1;
	*nb_arg = *nb_arg - 1;
}

void			replace_g_last(char **last, char *last_arg)
{
	free(*last);
	*last = ft_strdup(last_arg);
}

char			*check_validity(char *str, int i, t_shell *data)
{
	str = var_1(str, i, data);
	return (str);
}
