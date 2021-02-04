/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 15:11:13 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/27 11:21:23 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

void			exec_vague(char **func, t_shell *data, int j)
{
	int			i;
	char		*home;
	char		*home_final;
	char		*arg;
	char		*vague;

	i = 0;
	while (data->copyenv[i++])
	{
		home = ft_strnstr(data->copyenv[i], "HOME=", ft_strlen("HOME="));
		if (home)
			j = 1;
		if (j == 1)
			break ;
	}
	arg = ft_substr(func[0], 1, ft_strlen(func[0]));
	home_final = ft_substr(home, 5, ft_strlen(home));
	vague = ft_strjoin(home_final, arg);
	free(arg);
	free(home_final);
	execve(vague, func, data->copyenv);
	free(vague);
}

void			exec_bin(char **func, t_shell *data)
{
	int			i;

	i = 0;
	while (data->path_split[i])
	{
		data->bin = (char *)calloc(sizeof(char),
			(ft_strlen(data->path_split[i]) + 1 +
			ft_strlen(func[0]) + 1));
		fonction_cat_for_bin(data, func, i);
		g_error_bin = 0;
		execve(data->bin, func, data->copyenv);
		g_error_bin = 1;
		free(data->bin);
		free(func[0]);
		func[0] = ft_strdup(data->temp);
		free(data->temp);
		i++;
	}
}

void			exec_point(char **func, t_shell *data)
{
	char		*pwd;
	char		*pwd_direction;
	char		*temp;

	pwd = ft_strdup(pwd_for_exec_bin());
	pwd_direction = ft_strjoin(pwd, "/");
	temp = ft_strjoin(pwd_direction, func[0] + 2);
	free_chaine_three(pwd_direction, func[0], pwd);
	execve(temp, func, data->copyenv);
	free(temp);
}
