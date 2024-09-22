/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:25:42 by timanish          #+#    #+#             */
/*   Updated: 2024/07/04 15:03:13 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*save_check(char *save_buf, char *buf)
{
	if (!buf)
		return (NULL);
	if (!save_buf)
		save_buf = ft_strdup("");
	if (!save_buf)
		return (free (buf), NULL);
	return (save_buf);
}

char	*connect_buf(int fd, char *buf, char *save_buf)
{
	ssize_t	count;
	char	*join_buf;

	save_buf = save_check(save_buf, buf);
	if (!save_buf)
		return (NULL);
	count = 1;
	while (count > 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count <= 0)
			break ;
		buf[count] = '\0';
		join_buf = ft_strjoin(save_buf, buf);
		if (!join_buf)
			return (free (save_buf), free (buf), NULL);
		free (save_buf);
		save_buf = join_buf;
		if (ft_strchr(save_buf, '\n'))
			break ;
	}
	free (buf);
	if (count < 0 || (count == 0 && ft_strlen(save_buf) == 0))
		return (free (save_buf), NULL);
	return (save_buf);
}

char	*result_buf(char *save_buf, size_t i, char *re_buf)
{
	size_t	word;

	word = 0;
	if (!re_buf)
		return (NULL);
	while (word <= i)
	{
		re_buf[word] = save_buf[word];
		word ++;
	}
	re_buf[i + 1] = '\0';
	return (re_buf);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*save_buf[OPEN_MAX];
	char		*re_buf;
	size_t		i;
	char		*trim_buf;

	if (fd > OPEN_MAX || fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	save_buf[fd] = connect_buf(fd, buf, save_buf[fd]);
	if (!save_buf[fd])
		return (NULL);
	i = 0;
	while (save_buf[fd][i] != '\n' && save_buf[fd][i + 1] != '\0')
		i ++;
	re_buf = (char *)malloc(sizeof(char) * (i + 2));
	re_buf = result_buf(save_buf[fd], i, re_buf);
	trim_buf = ft_strdup(save_buf[fd] + (i + 1));
	if (!trim_buf)
		return (free (trim_buf), free (save_buf[fd]), free (re_buf), NULL);
	free (save_buf[fd]);
	save_buf[fd] = trim_buf;
	return (re_buf);
}
