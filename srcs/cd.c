/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:42:49 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/27 12:47:36 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

int			ft_no_arg(char **env)
{
	char	*path;

	ft_set_old_pwd(env);
	path = get_env(env, "HOME");
	chdir(path);
	if (errno != 0)
		ft_printf("%s: cd: %s: %s\n", SHELL, path, strerror(errno));
	errno = 0;
	g_return_valu = 0;
	return (0);
}

char		*get_oldpwd(char **env)
{
	char	*path;

	path = ft_strdup(get_env(env, "OLDPWD"));
	ft_printf("%s\n", path);
	return (path);
}

int			ft_cd(char **arg, char **env)
{
	char	*path;

	errno = 0;
	if (!arg[1])
		return (ft_no_arg(env));
	else
	{
		if (!ft_strcmp(arg[1], "-"))
			path = get_oldpwd(env);
		else if (arg[1][0] == '~')
			path = ft_strdup(get_env(env, "HOME"));
		else
			path = ft_strdup(arg[1]);
	}
	chdir(path);
	if (errno != 0)
	{
		ft_printf("%s: cd: %s: %s\n", SHELL, path, strerror(errno));
		g_return_valu = 1;
	}
	errno = 0;
	free(path);
	ft_set_old_pwd(env);
	ft_set_new_pwd(env);
	return (0);
}
