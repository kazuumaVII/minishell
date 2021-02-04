/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_matrice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:34:17 by nsimon            #+#    #+#             */
/*   Updated: 2021/01/22 12:38:14 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

char	**ft_matdup(char **mat)
{
	int		i;
	char	**dup;

	i = 0;
	while (mat[i])
		i++;
	if (!(dup = malloc(sizeof(*dup) * i + 1)))
		exit(EXIT_FAILURE);
	i = -1;
	while (mat[++i])
		dup[i] = ft_strdup(mat[i]);
	dup[i] = 0;
	return (dup);
}

char	**ft_sort_matrice(char **env)
{
	int		count;
	int		i;
	int		j;
	char	**new;
	char	*tmp;

	new = ft_matdup(env);
	count = 0;
	while (new[count])
		count++;
	i = -1;
	while (++i < count)
	{
		j = i;
		while (++j < count)
			if (ft_strcmp(new[i], new[j]) > 0)
			{
				tmp = new[i];
				new[i] = new[j];
				new[j] = tmp;
			}
	}
	return (new);
}
