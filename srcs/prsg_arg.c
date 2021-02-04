/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsg_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:04:34 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/20 17:02:05 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

void			parse_quotes(char *str)
{
	int			i;
	int			quote;
	int			dquote;

	quote = 0;
	dquote = 0;
	i = -1;
	while (str[++i])
	{
		if (i > 0 && str[i - 1] == -1)
			;
		else if (str[i] == '\'' && !dquote)
		{
			quote == 1 ? quote-- : quote++;
			str[i] = -2;
		}
		else if (str[i] == '"' && !quote)
		{
			dquote == 1 ? dquote-- : dquote++;
			str[i] = -2;
		}
	}
}

char			*parse_arg(char *str, t_shell *data)
{
	if (check_closed(str))
	{
		free(str);
		return (NULL);
	}
	if (!(str = parse_var(str, data)))
		return (NULL);
	if (ft_strncmp(str, "\x80\xf5", ft_strlen(str)))
	{
		parse_quotes(str);
		str = new_str_moove(str);
	}
	return (str);
}

int				is_valide(char *str, int index, int option)
{
	int			i;
	int			quote;
	int			dquote;

	i = 0;
	quote = 0;
	dquote = 0;
	while (str[i] && i < index)
	{
		if (str[i] == '"' && (i == 0 || (i > 0 && (str[i - 1] != -1)))
			&& !quote)
			dquote == 1 ? dquote-- : dquote++;
		else if (str[i] == '\'' && (i == 0 || (i > 0 && (str[i - 1] != -1)))
			&& !dquote)
			quote == 1 ? quote-- : quote++;
		i++;
	}
	if (!option && str[i] && !quote)
		return (0);
	if (option && !quote && !dquote)
		return (0);
	return (1);
}

void			prsg_slash(char *str)
{
	int			i;
	int			quote;
	int			dquote;

	quote = 0;
	dquote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' &&
			(i == 0 || (i > 0 && str[i - 1] != -1)) && !quote)
			dquote == 1 ? dquote-- : dquote++;
		else if (str[i] == '\'' &&
			(i == 0 || (i > 0 && str[i - 1] != -1)) && !dquote)
			quote == 1 ? quote-- : quote++;
		if (str[i] == '\\' && (i == 0 || (i > 0 && str[i - 1] != -1)))
		{
			if (!quote && !dquote)
				str[i] = -1;
			else if (dquote && str[i + 1] && ft_strchr("$\\\"", str[i + 1]))
				str[i] = -1;
		}
	}
}
