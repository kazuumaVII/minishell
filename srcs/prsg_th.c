/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsg_th.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:40:36 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/22 16:11:07 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

int				return_for_quote(void)
{
	ft_printf("minishell: error quote\n");
	g_return_valu = 1;
	return (g_return_valu);
}

int				check_closed(char *str)
{
	int			i;
	int			quote;
	int			dquote;

	quote = 0;
	dquote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (i > 0 && str[i - 1] == -1)
				;
			else if (str[i] == '\'' && !dquote)
				quote == 1 ? quote-- : quote++;
			else if (str[i] == '"' && !quote)
				dquote == 1 ? dquote-- : dquote++;
		}
	}
	if (dquote || quote)
	{
		return_for_quote();
		return (g_return_valu);
	}
	return (0);
}

char			*new_str_delete(char *str, int j)
{
	int			i;
	char		*new_str;

	if (!(new_str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] < 0)
			;
		else
			new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	return (new_str);
}

char			*new_str_moove(char *str)
{
	int			i;
	int			j;
	char		*new_str;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] > 0)
			j++;
	if (!j)
	{
		free(str);
		return (ft_strdup(""));
	}
	new_str = new_str_delete(str, j);
	free(str);
	return (new_str);
}

int				ft_nb_arg(char *str)
{
	int				j;
	int				i;

	i = 0;
	j = -1;
	while (str[++j] == ' ')
		;
	while (str[++j])
	{
		if (str[j] == ' ' && str[j + 1] && str[j + 1]
			!= ' ' && !is_valide(str, j, 1))
			i++;
	}
	return (i);
}
