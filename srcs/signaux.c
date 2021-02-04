/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:45:42 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/22 16:08:36 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

void			ctrl_c(int sig)
{
	int i;

	(void)sig;
	if (!g_pipe_pid)
	{
		write(1, "\nMINISHELL $> ", 14);
		g_return_valu = 130;
	}
	else
	{
		i = -1;
		while (++i)
			kill(g_pipe_pid[i], sig);
		write(1, "\n", 1);
		g_return_valu = 130;
	}
}

int				ctrl_d(void)
{
	ft_printf("exit\n");
	return (1);
}

int				main_signal(void)
{
	if (signal(SIGQUIT, &ctrl_slash_quit) == SIG_ERR)
	{
		ft_printf("Could not set signal handler\n");
		return (1);
	}
	if (signal(SIGINT, &ctrl_c) == SIG_ERR)
	{
		ft_printf("Could not set signal handler\n");
		return (1);
	}
	return (0);
}

void			ctrl_slash_quit(int sig)
{
	int i;

	i = -1;
	(void)sig;
	if (g_pipe_pid)
	{
		ft_printf("Quit: 3\n");
		while (++i)
			kill(g_pipe_pid[i], 2);
		g_return_valu = 131;
	}
	else
	{
		write(1, "\b\b  \b\b", 7);
		g_return_valu = 127;
	}
}
