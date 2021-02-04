/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aff_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 04:01:14 by nsimon            #+#    #+#             */
/*   Updated: 2021/01/27 11:20:24 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

char		*parse_value(char *str)
{
	int		i;
	int		j;
	int		size;
	char	*value;

	i = -1;
	size = 0;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '$' || str[i] == '`' || str[i] == '\\')
			size++;
		size++;
	}
	if (!(value = malloc(sizeof(*value) * size + 1)))
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '$' || str[i] == '`' || str[i] == '\\')
			value[j++] = '\\';
		value[j++] = str[i++];
	}
	value[j] = 0;
	return (value);
}

void		aff_var_env(char **env)
{
	int		i;
	char	name[PATH_MAX];
	char	*last;
	char	*value;
	char	**env_sort;

	i = 0;
	env_sort = ft_sort_matrice(env);
	while (env_sort[i])
	{
		if ((last = ft_memccpy(name, env_sort[i], '=', ft_strlen(env_sort[i]))))
			last[0] = 0;
		else
			name[ft_strlen(env_sort[i])] = 0;
		value = parse_value(&env_sort[i][ft_strlen(name)]);
		if (name[ft_strlen(name) - 1] == '=')
			ft_printf("declare -x %s\"%s\"\n", name, value);
		else
			ft_printf("declare -x %s\n", name);
		free(value);
		i++;
	}
	free_array(env_sort);
}
