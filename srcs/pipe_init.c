/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:04:26 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/27 12:47:43 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

void				start_init(char *str, int *start, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	*start = *i;
}

void				op_check(int op, int *j)
{
	if (op == 3)
		(*j) = (*j) + 1;
}

int					exit_fd(int fd, char **file)
{
	free(*file);
	return (fd);
}

int					get_fd(char *str, int option)
{
	char			*file;
	int				fd;
	int				start;
	int				i;

	i = 1;
	op_check(option, &i);
	fd = 0;
	start_init(str, &start, &i);
	while (str[i] && str[i] != ' ')
		i++;
	file = ft_substr(str, start, i - start);
	if (option == 1)
		fd = open(file, O_RDONLY);
	else if (option == 2)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (option == 3)
		fd = open(file, O_RDWR | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		ft_printf("minishell: %s: %s\n", file, strerror(errno));
	return (exit_fd(fd, &file));
}

int					init_pipe(int nb_pipe, int ***pipes)
{
	int				j;

	j = 0;
	if (nb_pipe)
	{
		if (!(*pipes = malloc(sizeof(int *) * nb_pipe)))
			return (0);
		while (j < nb_pipe)
		{
			(*pipes)[j] = NULL;
			if (!((*pipes)[j] = malloc(sizeof(int) * 2)))
				return (0);
			j++;
		}
	}
	return (1);
}
