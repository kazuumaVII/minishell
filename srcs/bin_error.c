/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:24:25 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/27 11:23:43 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

void			path_error(char **func)
{
	if (g_error_bin == 1)
	{
		ft_printf("minishell: %s : command not found\n", func[0]);
		g_return_valu = 127;
	}
}

int				check_error(char **str, int count)
{
	int			error;
	int			i;
	int			j;

	error = 0;
	i = 0;
	j = 1;
	if (count != 1)
	{
		if (str[j][i] == '-' || str[j][i] == '+')
			i++;
		while (str[j][i])
		{
			if (str[j][i] < '0' || str[j][i] > '9')
				break ;
			i++;
		}
		if (str[j][i] || (i == 1 && (str[j][i - 1] == '-'
			|| str[j][i - 1] == '+')))
			error = 255;
		else
			g_return_valu = ft_atoi(str[1]);
	}
	return (error);
}
