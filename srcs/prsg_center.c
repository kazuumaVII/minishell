/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsg_center.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:00:09 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/20 17:03:24 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

char			*craft_new_str(char *str, char *key, char *value, int index)
{
	char		*new_str;
	char		*after_var;

	if (ft_strlen(str) - ft_strlen(key) + ft_strlen(value) == 0)
		new_str = ft_strdup("");
	else if (!(new_str = malloc(sizeof(char) * (ft_strlen(str) -
		ft_strlen(key) + ft_strlen(value) + 1))))
		return (NULL);
	ft_strlcpy(new_str, str, index + 1);
	ft_strlcpy(new_str + ft_strlen(new_str), value, ft_strlen(value) + 1);
	after_var = &str[index + ft_strlen(key)];
	ft_strlcpy(new_str + ft_strlen(new_str), after_var,
		ft_strlen(after_var) + 1);
	return (new_str);
}

char			*var_1(char *str, int index, t_shell *data)
{
	char		*tab;
	char		*str_new;
	char		*value;

	if (!(tab = var_name_prsg(&str[index + 1])))
		return (str);
	value = prsg_valu(tab, data);
	str_new = craft_new_str(str, tab, value, index);
	free(tab);
	free(value);
	free(str);
	return (str_new);
}

int				is_correct(char *str, int i)
{
	if (str[i] == '$' && !is_valide(str, i, 0) && (i == 0 ||
		(i > 0 && str[i - 1] != -1)) && (ft_isalnum(str[i + 1]) ||
		str[i + 1] == '_' || str[i + 1] == '{' || str[i + 1] == '?' ||
		str[i + 1] == '[' || str[i + 1] == '#' || str[i + 1] == '&' ||
		str[i + 1] == '!' || str[i + 1] == '@' || str[i + 1] == '*' ||
		str[i + 1] == '_' || str[i + 1] == '{' || str[i + 1] == '?' ||
		str[i + 1] == '$'))
		return (1);
	return (0);
}

int				create_tab(char *str, char **tab, t_shell *data, int nb_arg)
{
	int			j;
	int			i;

	j = 0;
	while (j < nb_arg)
	{
		i = -1;
		while (*str == ' ')
			str++;
		while (str[++i])
			if (str[i] == ' ' && !is_valide(str, i, 1))
				break ;
		if (!(tab[j++] = parse_arg(ft_substr(str, 0, i), data)))
		{
			clean_array(tab);
			return (0);
		}
		if (!ft_strncmp(tab[j - 1], "\x80\xf5", 3))
			free_handle_arg(&tab[j - 1], &j, &nb_arg);
		str = str + i;
	}
	tab[j] = NULL;
	return (1);
}

char			**prsg_center(char *str, t_shell *data)
{
	char		**tab;
	int			nb_arg;
	int			j;

	if (!str || !ft_strlen(str))
		return (NULL);
	prsg_slash(str);
	nb_arg = ft_nb_arg(str) + 1;
	if (!(tab = malloc(sizeof(char *) * (nb_arg + 1))))
		return (NULL);
	if (!(create_tab(str, tab, data, nb_arg)))
		return (NULL);
	j = 0;
	while (tab[j])
		j++;
	replace_g_last(&g_last, tab[j - 1]);
	return (tab);
}
