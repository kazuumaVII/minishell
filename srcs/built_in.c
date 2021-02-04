/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:49:23 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/27 12:50:14 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

int				echo_test_option(char *str)
{
	int			i;

	if (str)
	{
		if (str[0] != '-')
			return (0);
		i = 1;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

int				ft_cmd_echo(char **str, char **env)
{
	int			i;
	int			j;
	int			flag;

	i = 1;
	flag = 0;
	while (echo_test_option(str[i]))
	{
		i++;
		flag = 1;
	}
	j = i;
	while (str[i])
	{
		if (i > j)
			ft_putchar(' ');
		if (ft_strcmp(str[i], "~") == 0)
			ft_putstr(get_env(env, "HOME"));
		else
			ft_putstr(str[i]);
		i++;
	}
	if (!flag)
		ft_putchar('\n');
	return (0);
}

int				ft_pwd(char **env)
{
	char		*s;

	g_return_valu = 0;
	s = getcwd(NULL, 0);
	if (s == NULL)
		ft_printf("%s\n", get_env(env, "PWD"));
	else
	{
		ft_printf("%s\n", s);
		free(s);
	}
	return (g_return_valu);
}

int				check_numeric(char **str)
{
	int			arg_count;
	int			num_error;

	arg_count = 0;
	num_error = 0;
	while (str[arg_count])
		arg_count++;
	num_error = check_error(str, arg_count);
	if (num_error)
	{
		g_return_valu = 255;
		ft_printf("exit\nminishell: exit: %s mumeric argument \
			required\n", str[1]);
		exit(g_return_valu);
	}
	if (arg_count > 2)
	{
		g_return_valu = 1;
		ft_printf("exit\nminishell: exit: Too many arguments\n");
		return (g_return_valu);
	}
	return (0);
}

int				ft_exit(char **str, char **env)
{
	int arg_error;

	(void)**env;
	arg_error = check_numeric(str);
	if (arg_error == 0)
	{
		ft_printf("exit\n");
		exit(g_return_valu);
	}
	return (g_return_valu);
}
