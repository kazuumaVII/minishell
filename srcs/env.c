/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:49:37 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/27 12:50:08 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

void			print_for_export(char **str, int i)
{
	ft_printf("%s: export: `%s': not a valid identifier\n",
				SHELL, str[i]);
}

void			ft_env_var(t_shell *data)
{
	int		i;
	char	**env;

	i = 0;
	env = data->copyenv;
	while (env[i])
	{
		if (ft_strnstr(env[i], "=", ft_strlen(env[i])))
			ft_printf("%s\n", env[i]);
		i++;
	}
}

int				ft_full_space(char *str)
{
	int		i;

	i = 0;
	{
		while (str[i])
		{
			if (!(str[i] == ' '))
				return (0);
			else
				i++;
		}
	}
	return (1);
}

void			free_last_v(char *str, t_shell *data)
{
	free(str);
	free(data->buffer);
	free_array(data->copyenv);
}
