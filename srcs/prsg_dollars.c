/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsg_dollars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:50:55 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/27 12:50:58 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

char		*find_env_name(char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	new = malloc(sizeof(*new) * (i + 1));
	if (!new)
		exit(9);
	ft_strlcpy(new, str, i + 1);
	return (new);
}

char		*join_str(char *var1, char *var2)
{
	if (!var1)
		return (ft_strjoin("", var2));
	if (!var2)
		return (ft_strjoin(var1, ""));
	return (ft_strjoin(var1, var2));
}

char		*replace_env(char *str, char **env)
{
	int		i;
	char	*new;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	new = malloc(sizeof(*new) * (i + 1));
	if (!new)
		exit(9);
	ft_strncpy(new, str, i);
	new[i] = 0;
	if (!str[i])
		return (new);
	tmp = find_env_name(&str[++i]);
	tmp2 = get_env(env, tmp);
	free(tmp);
	tmp = join_str(new, tmp2);
	free(new);
	while (ft_isalnum(str[i]))
		i++;
	new = join_str(tmp, &str[i]);
	free(tmp);
	return (new);
}

char		*find_dollar(char *str, int *quote)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			*quote = *quote + 1;
		if (str[i] == '$' && *quote % 2 == 0 && str[i - 1] != '\\')
			return (ft_strnstr(str, "$", ft_strlen(str)));
		i++;
	}
	return (NULL);
}

void		parse_dollar(char **buffer, char **env)
{
	int		i;
	int		quote;
	char	**split;
	char	*tmp;

	split = ft_split(*buffer, ' ');
	i = 0;
	quote = 0;
	while (split[i])
	{
		tmp = find_dollar(split[i], &quote);
		if (tmp && (ft_isalpha(tmp[1]) || tmp[1] == '_'))
		{
			tmp = replace_env(split[i], env);
			if (!tmp)
				tmp = ft_strdup("");
			free(split[i]);
			split[i] = tmp;
		}
		else
			i++;
	}
	free(*buffer);
	*buffer = ft_strcomb(split, " ");
	free_array(split);
}
