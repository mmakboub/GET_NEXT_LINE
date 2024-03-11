/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:27:05 by mmakboub          #+#    #+#             */
/*   Updated: 2021/12/19 22:24:39 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(char *rest)
{
	int		len;
	char	*str;

	len = 0;
	while (rest[len] && rest[len] != '\n')
		len++;
	str = ft_substr(rest, 0, len + 1);
	return (str);
}

char	*rest_line(char *rest)
{
	char	*ptr;
	int		len;

	len = 0;
	while (rest[len] && rest[len] != '\n')
		len++;
	ptr = ft_substr(rest, len + 1, ft_strlen(rest) - len + 1);
	free(rest);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*rest[1024];
	char		buffer[BUFFER_SIZE + 1];
	int			rd;
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	rd = 1;
	while (rd != 0 && !ft_strchr(rest[fd], '\n'))
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		buffer[rd] = '\0';
		if (rd < 0)
			return (NULL);
		rest[fd] = ft_strjoin(rest[fd], buffer);
	}
	if (!rest[fd][0])
	{
		free (rest[fd]);
		rest[fd] = NULL;
		return (NULL);
	}
	newline = get_line(rest[fd]);
	rest[fd] = rest_line(rest[fd]);
	return (newline);
}
