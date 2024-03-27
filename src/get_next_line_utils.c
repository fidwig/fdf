/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:24:41 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/27 16:08:20 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	hasendl(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

void	trim_buf(char *buf)
{
	int	i;
	int	j;

	i = 0;
	while (i < BUFFER_SIZE && buf[i] && buf[i] != '\n')
		i++;
	j = 0;
	i++;
	while (i < BUFFER_SIZE && buf[i])
		buf[j++] = buf[i++];
	while (j < BUFFER_SIZE)
		buf[j++] = '\0';
}

char	*complete_line(char *line, char *buf)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (line[i])
		i++;
	j = 0;
	while (j < BUFFER_SIZE && buf[j] && buf[j - 1] != '\n')
		j++;
	s = (char *) malloc((i + j + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (line[j])
		s[i++] = line[j++];
	j = 0;
	while (j < BUFFER_SIZE && buf[j] && buf[j - 1] != '\n')
		s[i++] = buf[j++];
	s[i] = '\0';
	free(line);
	return (s);
}

char	*read_and_complete(char *line, char *buf, int fd, ssize_t *bytes_read)
{
	ssize_t	i;

	*bytes_read = read(fd, buf, BUFFER_SIZE);
	if (*bytes_read == 0 && line[0])
		return (line);
	if (*bytes_read < 1)
	{
		free(line);
		return (NULL);
	}
	i = *bytes_read;
	if (i < BUFFER_SIZE)
		buf[i++] = '\0';
	line = complete_line(line, buf);
	return (line);
}
