/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 19:29:04 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/22 16:10:17 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

int				arg_valid(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (1);
	return (0);
}

int				arg_pipe(t_strt *strt)
{
	int			i;

	i = -1;
	while (strt[++i].str)
	{
		if (!ft_strlen(strt[i].str) || !arg_valid(strt[i].str))
		{
			ft_printf("minishell: error syntax pipe\n");
			g_return_valu = 258;
			return (-1);
		}
	}
	return (0);
}

int				is_backslash(char *str, int index)
{
	int			backslash;

	backslash = 0;
	while (index >= 0 && str[index] == '\\')
	{
		index--;
		backslash++;
	}
	if (backslash != 0 && backslash % 2 != 0)
		return (1);
	return (0);
}
