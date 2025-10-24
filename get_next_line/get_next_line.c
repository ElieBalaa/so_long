/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 21:46:51 by the-flash         #+#    #+#             */
/*   Updated: 2025/05/25 23:50:58 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_read(int fd, char *stash)
{
	ssize_t	bytes_read;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = gnl_strjoin(stash, buffer);
		if (!stash)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (stash);
}

static char	*gnl_extract_and_update(char **stash)
{
	char	*line;
	char	*nl;
	char	*new_stash;

	nl = ft_strchr(*stash, '\n');
	if (nl)
	{
		line = gnl_substr(*stash, 0, nl - *stash + 1);
		new_stash = gnl_substr(*stash,
			nl - *stash + 1,
			gnl_strlen(*stash) - (nl - *stash + 1));
	}
	else
	{
		line = gnl_substr(*stash, 0, gnl_strlen(*stash));
		new_stash = NULL;
	}
	free(*stash);
	*stash = new_stash;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = gnl_read(fd, stash);
	if (!stash || stash[0] == '\0')
	{
		if (stash)
		{
			free(stash);
			stash = NULL;
		}
		return (NULL);
	}
	line = gnl_extract_and_update(&stash);
	return (line);
}
