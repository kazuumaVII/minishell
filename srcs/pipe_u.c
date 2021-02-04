/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:45:54 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/27 11:19:00 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

void			wait_pids(pid_t *pids, int size, t_strt *strt)
{
	int			i;
	int			status;

	i = -1;
	(void)strt;
	while (++i < size)
	{
		if (pids[i] == -1)
			;
		else
		{
			waitpid(pids[i], &status, 0);
			if (WIFEXITED(status))
				g_return_valu = WEXITSTATUS(status);
		}
	}
}

void			clean_pipe(int **pipes, int nb_pipe)
{
	int			j;

	j = 0;
	if (nb_pipe)
	{
		while (j < nb_pipe)
		{
			free(pipes[j]);
			j++;
		}
	}
	if (pipes)
	{
		free(pipes);
	}
}

void			clean_strt(t_strt *strt)
{
	int i;

	i = -1;
	while (strt[++i].str)
		free(strt[i].str);
	free(strt);
}

int				free_clean_input(t_strt *strt, int **pipes, int nb_pipe)
{
	clean_strt(strt);
	clean_pipe(pipes, nb_pipe);
	free(g_pipe_pid);
	return (0);
}

t_strt			*init_array(char *str)
{
	t_strt		*strt;

	if (!(strt = malloc(sizeof(t_strt) * (ft_nb_pipe(str, 0) + 2))))
		return (NULL);
	if (!(g_pipe_pid = malloc(sizeof(pid_t) * (ft_nb_pipe(str, 0) + 2))))
	{
		ft_printf("minishell: malloc failed\n");
		return (NULL);
	}
	return (strt);
}
