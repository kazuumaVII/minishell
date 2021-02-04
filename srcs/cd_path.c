/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:57:49 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/27 12:47:17 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

char		*ft_old_path(char **env)
{
	int		i;
	char	*path;
	int		j;

	i = ft_search_str("OLDPWD", env);
	path = ft_strnew(PATH_MAX);
	j = 0;
	while (env[i][j + 7])
	{
		path[j] = env[i][j + 7];
		j++;
	}
	ft_putstr_fd(path, 1);
	ft_set_old_pwd(env);
	return (path);
}

char		**ft_cd_path(char **env)
{
	char	*path;

	path = ft_old_path(env);
	chdir(path);
	free(path);
	return (env);
}

char		**ft_env(char **arg, char **env)
{
	int		i;
	char	*str;

	if (!arg[0] || !arg[1] || arg[2])
		return (env);
	i = ft_search_str(arg[0], env);
	if (env[i])
	{
		str = ft_mystr(arg[0], arg[1], '=');
		free(env[i]);
		env[i] = str;
	}
	else
	{
		str = ft_mystr(arg[0], arg[1], '=');
		env[i] = str;
		env[i + 1] = NULL;
	}
	return (env);
}

void		ft_set_old_pwd(char **env)
{
	char	**arg;

	arg = (char **)malloc(sizeof(char *) * 3);
	arg[0] = ft_strdup("OLDPWD");
	arg[1] = ft_strdup(get_env(env, "PWD"));
	arg[2] = NULL;
	errno = 0;
	ft_env(arg, env);
	free(arg[0]);
	free(arg[1]);
	free(arg[2]);
	free(arg);
}

void		ft_set_new_pwd(char **env)
{
	char	**arg;

	arg = (char **)malloc(sizeof(char *) * 3);
	arg[0] = ft_strdup("PWD");
	arg[1] = NULL;
	arg[1] = getcwd(arg[1], PATH_MAX);
	arg[2] = NULL;
	if (errno != 0)
	{
		ft_printf("cd: error retrieving current directory: getcwd: "
				"cannot access parent directories: %s\n", strerror(errno));
	}
	errno = 0;
	ft_env(arg, env);
	free(arg[0]);
	free(arg[1]);
	free(arg[2]);
	free(arg);
}
