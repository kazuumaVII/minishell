/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:45:13 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/20 16:51:09 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

int			ft_search_str(char *str, char **env)
{
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (str[j] && env[i][j] != '=' && (str[j] == env[i][j]))
		{
			if (str[j] == env[i][j])
				j++;
			if (str[j] == '\0' && env[i][j] == '=')
				return (i);
		}
		i++;
	}
	return (i);
}

char		*strnew_ff(size_t size)
{
	char	*str;
	size_t	len;

	len = 0;
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (len < size)
	{
		str[len] = '\0';
		len++;
	}
	str[len] = 0;
	return (str);
}

char		*ft_mystr(char *str_1, char *str_2, char c)
{
	int		i;
	int		j;
	int		k;
	char	*tab;

	i = ft_strlen(str_1);
	j = ft_strlen(str_2);
	tab = strnew_ff(i + j + 1);
	k = 0;
	while (k < i)
	{
		tab[k] = str_1[k];
		k++;
	}
	tab[k] = c;
	i = 0;
	k++;
	while (i < j)
	{
		tab[k] = str_2[i];
		i++;
		k++;
	}
	tab[k] = '\0';
	return (tab);
}

char		*ft_strnew(size_t size)
{
	char	*str;
	int		i;

	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
	str[i] = 0;
	return (str);
}
