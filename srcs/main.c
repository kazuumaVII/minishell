/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:49:55 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/27 12:49:58 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

void			ft_close_pipes(int **pipes, int size)
{
	int			i;

	i = -1;
	while (++i < size)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

int				ft_prsg_pipe(char *str, t_strt *strt)
{
	int			i;
	int			j;

	j = 0;
	i = 0;
	while (ft_nb_pipe(str + j, 1) != -1)
	{
		strt[i].str = ft_substr(str + j, 0,
			ft_nb_pipe(str + j, 1));
		j += ft_strlen(strt[i].str) + 1;
		i++;
	}
	strt[i].str = ft_substr(str + j, 0, ft_strlen(str + j));
	strt[i + 1].str = NULL;
	if (arg_pipe(strt) == -1)
		return (-1);
	return (0);
}

int				*splitsaisie(t_shell *data)
{
	char		**arg_p;
	int			i;

	arg_p = NULL;
	i = -1;
	recupere_le_path(data);
	parse_dollar(&data->buffer, data->copyenv);
	if (data->buffer[0] == '\0' || data->buffer[0] == ' ')
		return (0);
	arg_p = parse_v2(data->buffer);
	while (arg_p[++i])
		ft_exec_pipe(arg_p[i], data);
	free_array(arg_p);
	free_array(data->path_split);
	return (0);
}

int				prompt(t_shell *data)
{
	int			no_buff;

	no_buff = 0;
	while (1)
	{
		g_pipe_pid = NULL;
		if (!gnl_ctrl_input(0, &data->buffer, &no_buff, 1))
		{
			if (ctrl_d())
				break ;
		}
		else if (data->buffer[0] == '\0' || (data->buffer[0] == ' ' &&
				ft_full_space(data->buffer)))
			write(1, "MINISHELL $> ", 13);
		else
		{
			splitsaisie(data);
			write(1, "MINISHELL $> ", 13);
		}
		free(data->buffer);
	}
	free_last_v(g_last, data);
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_shell		data;

	g_pipe_pid = NULL;
	(void)ac;
	(void)av;
	print_home();
	write(1, "MINISHELL $> ", 13);
	ft_copy_tab2d(&data, env);
	main_signal();
	prompt(&data);
	return (0);
}
