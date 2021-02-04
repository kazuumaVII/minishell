/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_center.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:02:05 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/27 12:36:46 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

void				prep_exec(t_strt *strt, char **func, t_shell *data)
{
	int				fds[2];

	fds[0] = dup(0);
	fds[1] = dup(1);
	g_return_valu = 0;
	fd_center(strt);
	ft_exec_builtin(strt, func, data);
	clean_array(func);
	dup2(fds[0], 0);
	dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
}

int					ft_exec_builtin(t_strt *strt, char **func, t_shell *data)
{
	(void)*strt;
	g_return_valu = 0;
	if (!ft_strncmp(func[0], "echo", 5))
		ft_cmd_echo(func, data->copyenv);
	else if (!ft_strncmp(func[0], "pwd", 3))
		return (ft_pwd(data->copyenv));
	else if (!ft_strncmp(func[0], "cd", 2))
		ft_cd(func, data->copyenv);
	else if (!ft_strncmp(func[0], "export", 6))
		ft_export(func, data);
	else if (!ft_strncmp(func[0], "unset", 6))
		ft_unset(func, data);
	else if (!ft_strncmp(func[0], "env", 400))
		ft_env_var(data);
	else if (!ft_strncmp(func[0], "exit", 5))
		ft_exit(func, data->copyenv);
	else
	{
		bin_center(data, func);
		return (g_return_valu);
	}
	return (g_return_valu);
}

int					is_bin(char **func, t_shell *data)
{
	char			*path;
	struct stat		stats;
	int				i;

	i = -1;
	if (data->path_split)
	{
		while (data->path_split[++i])
		{
			if (i == 0)
				path = ft_strjoin(data->path_split[i] + 5, "/");
			else
				path = ft_strjoin(data->path_split[i], "/");
			path = ft_strjoin_s1(path, func[0]);
			if (stat(path, &stats) != -1)
			{
				free(path);
				return (0);
			}
			free(path);
		}
	}
	return (-1);
}

pid_t				ft_pipes_exec(t_strt *strt, int **pipes, int size,
								t_shell *data)
{
	pid_t			pid;
	char			**func;

	if (!(func = prsg_center(strt->str, data)))
		return (1);
	if (is_bin(func, data) == -1)
	{
		g_error_bin = 1;
		pid = -1;
		path_error(func);
		clean_array(func);
		return (pid);
	}
	if ((pid = fork()) == 0)
	{
		fd_center(strt);
		ft_close_pipes(pipes, size);
		exit(ft_exec_builtin(strt, func, data));
	}
	free_array(func);
	return (pid);
}

void				no_pipe_exec(t_strt *strt, t_shell *data)
{
	char			**func;
	pid_t			pid;

	if (!(func = prsg_center(strt->str, data)))
		return ;
	if (is_built_in(func[0]) == 0)
	{
		prep_exec(strt, func, data);
		return ;
	}
	if ((pid = fork()) == 0)
	{
		if (is_built_in(func[0]) == 1)
		{
			fd_center(strt);
			bin_center(data, func);
		}
		exit(g_return_valu);
	}
	clean_array(func);
	wait_pids(&pid, 1, strt);
	return ;
}
