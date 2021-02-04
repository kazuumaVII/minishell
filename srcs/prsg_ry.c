/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsg_ry.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 22:31:16 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/22 13:58:29 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

int				len_tab(char **tab)
{
	int			j;

	j = 0;
	while (tab[j])
		j++;
	return (j);
}

void			ft_copy_tab2d(t_shell *data, char **original)
{
	int			i;
	int			len;

	i = 0;
	len = len_tab(original);
	if (!(data->copyenv = ft_calloc(sizeof(char *), (len) + 1)))
		exit(SIGABRT);
	while (original[i])
	{
		data->copyenv[i] = ft_strdup(original[i]);
		i++;
	}
	data->copyenv[i] = NULL;
}

void			free_array(char **array)
{
	int			i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

char			*get_env(char **env, char *str)
{
	int			i;
	int			j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (str[j] && env[i][j] && env[i][j] == str[j])
			j++;
		if (str[j] == '\0' && (env[i][j] == '=' || env[i][j] == '\0'))
			return (&env[i][j + 1]);
	}
	return (NULL);
}

void			recupere_le_path(t_shell *data)
{
	data->env_path = NULL;
	data->env_path = get_env(data->copyenv, "PATH");
	if (data->env_path == NULL)
		data->env_path = ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:"
							"/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:"
							"/snap/bin");
	data->path_split = NULL;
	data->path_split = ft_split(data->env_path, ':');
}
