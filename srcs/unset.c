/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 02:10:24 by nsimon            #+#    #+#             */
/*   Updated: 2021/01/25 04:19:46 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

void	del_var_env(char *key, t_shell *data)
{
	int		i;
	int		j;
	int		size;
	char	**new;

	i = -1;
	j = 0;
	size = env_size(data->copyenv);
	new = malloc(sizeof(*new) * (size + 1));
	while (++i < size)
	{
		if (ft_strncmp(key, data->copyenv[i], ft_strlen(key)) == 0
			&& (data->copyenv[i][ft_strlen(key)] == '='
			|| data->copyenv[i][ft_strlen(key)] == '\0'))
			continue ;
		new[j++] = ft_strdup(data->copyenv[i]);
	}
	new[j] = 0;
	free_array(data->copyenv);
	data->copyenv = new;
}

void	ft_unset(char **cmd, t_shell *data)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	g_return_valu = 0;
	while (cmd[++i])
	{
		j = get_id(cmd[i]);
		if (cmd[i][j] != '\0')
		{
			ft_printf("%s: unset: `%s': not a valid identifier\n", SHELL,
				cmd[i]);
			g_return_valu = 1;
			continue ;
		}
		if (!(key = malloc(sizeof(*key) * j)))
			exit(EXIT_FAILURE);
		ft_strncpy(key, cmd[i], j);
		key[j] = 0;
		if (get_env(data->copyenv, key))
			del_var_env(key, data);
		free(key);
	}
}
