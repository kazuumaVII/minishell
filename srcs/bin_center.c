/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_center.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:32:30 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/27 12:47:12 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

void			free_chaine_three(char *str_1, char *str_2, char *str_3)
{
	free(str_1);
	free(str_2);
	free(str_3);
}

char			*pwd_for_exec_bin(void)
{
	char		buff[1024];
	char		*pwd;

	ft_memset(&buff, 0, 1024);
	pwd = getcwd(buff, 1024);
	if (!pwd)
		ft_printf("%s\n", strerror(errno));
	return (pwd);
}

void			bin_center(t_shell *data, char **func)
{
	int			j;

	j = 0;
	if (func[0][0] == '.' && func[0][1] == '.')
		execve(func[0], func, data->copyenv);
	else if (func[0][0] == '~')
		exec_vague(func, data, j);
	else if (func[0][0] != '/' && func[0][0] != '~' &&
			ft_strncmp(func[0], "./", 2) != 0)
		exec_bin(func, data);
	if (func[0][0] == '.')
		exec_point(func, data);
	if (func[0][0] == '/')
		execve(func[0], func, data->copyenv);
	g_error_bin = 1;
	path_error(func);
}
