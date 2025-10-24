/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/27 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_fd_list	*find_fd(t_fd_list **head, int fd)
{
	t_fd_list	*current;
	t_fd_list	*new_node;

	current = *head;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	new_node = malloc(sizeof(t_fd_list));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->stash = NULL;
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

static void	remove_fd(t_fd_list **head, int fd)
{
	t_fd_list	*current;
	t_fd_list	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			if (current->stash)
				free(current->stash);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

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
		stash = ft_strjoin(stash, buffer);
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
		line = ft_substr(*stash, 0, nl - *stash + 1);
		new_stash = ft_substr(*stash,
				nl - *stash + 1,
				ft_strlen(*stash) - (nl - *stash + 1));
	}
	else
	{
		line = ft_substr(*stash, 0, ft_strlen(*stash));
		new_stash = NULL;
	}
	free(*stash);
	*stash = new_stash;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list;
	t_fd_list			*fd_node;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_node = find_fd(&fd_list, fd);
	if (!fd_node)
		return (NULL);
	fd_node->stash = gnl_read(fd, fd_node->stash);
	if (!fd_node->stash || fd_node->stash[0] == '\0')
	{
		remove_fd(&fd_list, fd);
		return (NULL);
	}
	line = gnl_extract_and_update(&fd_node->stash);
	if (!fd_node->stash)
		remove_fd(&fd_list, fd);
	return (line);
}
