/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carltruj <carltruj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:49:19 by carltruj          #+#    #+#             */
/*   Updated: 2026/01/03 14:17:43 by carltruj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_extrac_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i + (stash[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*newstash;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	newstash = malloc(ft_strlen(stash) - i + 1);
	if (!newstash)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		newstash[j++] = stash[i++];
	newstash[j] = '\0';
	free(stash);
	return (newstash);
}

static char	*ft_read_and_join(int fd, char *stash, char *buf, ssize_t *bytes)
{
	*bytes = read(fd, buf, BUFFER_SIZE);
	if (*bytes < 0)
	{
		free(buf);
		free(stash);
		return (NULL);
	}
	buf[*bytes] = '\0';
	stash = ft_strjoin(stash, buf);
	if (!stash)
	{
		free(buf);
		return (NULL);
	}
	return (stash);
}

static char	*ft_read_to_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes = 1;
	while ((stash == NULL || !ft_strchr(stash, '\n')) && bytes > 0)
	{
		stash = ft_read_and_join(fd, stash, buf, &bytes);
		if (!stash)
			return (NULL);
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_read_to_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_extrac_line(stash[fd]);
	stash[fd] = ft_clean_stash(stash[fd]);
	return (line);
}
