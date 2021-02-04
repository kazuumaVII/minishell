/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:44:50 by frfrance          #+#    #+#             */
/*   Updated: 2020/12/02 20:45:41 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

int			input_pipe_arg(t_strt *strt, int j)
{
	if (strt->str[j] == '<' && !is_backslash(strt->str, j - 1))
	{
		if (strt->input_s != -1)
			close(strt->input_s);
		if ((strt->input_s = get_fd(&strt->str[j], 1)) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int			output_pipe_arg(t_strt *strt, int j)
{
	if (strt->str[j] == '>' && !is_backslash(strt->str, j - 1))
	{
		if (strt->output_s != -1)
			close(strt->output_s);
		if (strt->str[j + 1] && strt->str[j + 1] == '>')
		{
			if ((strt->output_s = get_fd(&strt->str[j], 3)) == -1)
				return (-1);
			j++;
		}
		else if ((strt->output_s = get_fd(&strt->str[j], 2)) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

void		pipe_arg(t_strt *strt)
{
	int		i;
	int		start;
	char	*str;

	i = -1;
	str = NULL;
	while (strt->str[++i] == ' ')
		;
	start = i;
	i--;
	while (strt->str[++i])
	{
		if ((strt->str[i] == '>' || strt->str[i] == '<')
			&& !is_valide(strt->str, i, 1) && !is_backslash(strt->str, i - 1))
		{
			if (start == i)
				str = NULL;
			else
				str = ft_substr(strt->str, 0, i);
			free(strt->str);
			strt->str = str;
			return ;
		}
	}
}

int			input_or_output(t_strt *strt, int *input_p, int *output_p)
{
	int		i;
	int		ret;

	i = -1;
	while (strt->str[++i])
	{
		if (strt->str[i] == '<' && !is_valide(strt->str, i, 1))
		{
			ret = input_pipe_arg(strt, i);
			if (ret == -1)
				return (EXIT_FAILURE);
			else if (ret == 1)
				*input_p = 1;
		}
		if (strt->str[i] == '>' && (i == 0 || strt->str[i - 1] != '>')
			&& !is_valide(strt->str, i, 1))
		{
			ret = output_pipe_arg(strt, i);
			if (ret == -1)
				return (EXIT_FAILURE);
			else if (ret == 1)
				*output_p = 1;
		}
	}
	return (EXIT_SUCCESS);
}

void		ft_redirec_for_pipe(t_strt *strt)
{
	int		input_p;
	int		output_p;

	strt->input_s = -1;
	strt->output_s = -1;
	input_p = 0;
	output_p = 0;
	if (input_or_output(strt, &input_p, &output_p) == 1)
	{
		strt->input_s = -1;
		return ;
	}
	if (!input_p)
		strt->input_s = 0;
	if (!output_p)
		strt->output_s = 1;
	pipe_arg(strt);
}
