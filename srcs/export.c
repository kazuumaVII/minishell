/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 02:43:01 by nsimon            #+#    #+#             */
/*   Updated: 2021/01/25 04:11:49 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

int			get_id(char *str)
{
	int		i;

	i = 0;
	if (!ft_isalpha(str[i]))
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

void		replace_var_env(char *key, char *str, t_shell *data)
{
	int		i;
	int		size;

	i = -1;
	size = env_size(data->copyenv);
	if (str[ft_strlen(key)] != '=')
		return ;
	while (++i < size)
		if (ft_strncmp(key, data->copyenv[i], ft_strlen(key)) == 0
			&& (data->copyenv[i][ft_strlen(key)] == '='
			|| data->copyenv[i][ft_strlen(key)] == '\0'))
		{
			free(data->copyenv[i]);
			data->copyenv[i] = ft_strdup(str);
		}
}

void		add_var_env(char *str, t_shell *data)
{
	int		i;
	int		size;
	char	**new;

	i = -1;
	size = env_size(data->copyenv);
	new = malloc(sizeof(*new) * (size + 2));
	while (++i < size)
		new[i] = ft_strdup(data->copyenv[i]);
	new[i++] = ft_strdup(str);
	new[i] = 0;
	free_array(data->copyenv);
	data->copyenv = new;
}

void		ft_export(char **cmd, t_shell *data)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	if (cmd[1] == NULL)
		aff_var_env(data->copyenv);
	while (cmd[++i])
	{
		j = get_id(cmd[i]);
		if (cmd[i][j] != '=' && cmd[i][j] != '\0')
		{
			print_for_export(cmd, i);
			g_return_valu = 1;
			continue ;
		}
		if (!(key = malloc(sizeof(*key) * j)))
			exit(EXIT_FAILURE);
		ft_strncpy(key, cmd[i], j);
		if (get_env(data->copyenv, key))
			replace_var_env(key, cmd[i], data);
		else
			add_var_env(cmd[i], data);
		free(key);
	}
}
