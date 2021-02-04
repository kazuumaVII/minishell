/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 21:25:48 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/25 04:07:18 by nsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_shell.h"

char	*ft_strcomb(char **split, char *sep)
{
	int		i;
	char	*str;
	char	*tmp;

	str = NULL;
	if (split)
	{
		i = 0;
		str = ft_strdup(split[i++]);
		while (split[i])
		{
			tmp = ft_strjoin(str, sep);
			free(str);
			str = ft_strjoin(tmp, split[i]);
			free(tmp);
			i++;
		}
	}
	return (str);
}

char	*ft_refresh_stock(char *stock, int i)
{
	char			*temp;

	if (stock[i])
	{
		temp = ft_strdup(stock + i + 1);
		free(stock);
	}
	else
	{
		free(stock);
		temp = NULL;
	}
	return (temp);
}

int		ft_free_all(int ret, char **buffer, char **stock)
{
	if (ret >= 0 && (*buffer || *stock))
	{
		if (*buffer)
			free(*buffer);
		if (ret == 0 && *stock)
			free(*stock);
	}
	if (ret == -1)
	{
		if (!*buffer)
			free(*buffer);
		if (*stock)
			free(*stock);
	}
	return (ret);
}

int		no_buffer(int *no_buff, int ret, char **buffer, char **stock)
{
	if (*no_buff != 2)
		*no_buff = 0;
	(*buffer)[ret] = '\0';
	*stock = ft_strjoin_s1(*stock, *buffer);
	if (*no_buff != 2 && (*buffer)[ret - 1] != '\n')
	{
		*no_buff = 1;
		write(1, "  \b\b", 4);
	}
	return (1);
}

int		gnl_ctrl_input(int fd, char **line, int *no_buff, int option)
{
	static char		*stock;
	char			*buffer;
	int				ret;
	int				i;

	if (BUFFER_SIZE <= 0 || !line || (ret = 0) ||
		!(buffer = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1))))
		return (ft_free_all(-1, &buffer, &stock));
	if (!stock)
		stock = (char *)ft_calloc(sizeof(char), 1);
	while (!ft_strchr(buffer, '\n') && ((ret = read(fd, buffer, BUFFER_SIZE))
		|| (ret == 0 && *no_buff && option == 1)))
	{
		if (ret == -1)
			return (ft_free_all(-1, &buffer, &stock));
		no_buffer(no_buff, ret, &buffer, &stock);
	}
	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	*line = ft_substr(stock, 0, i);
	stock = ft_refresh_stock(stock, i);
	if (ret || stock)
		return (ft_free_all(1, &buffer, &stock));
	return (ft_free_all(0, &buffer, &stock));
}
