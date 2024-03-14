/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:18:41 by jsommet           #+#    #+#             */
/*   Updated: 2023/12/15 20:28:41 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*line;
	ssize_t			bytes_read;
	static char		buf[BUFFER_SIZE];

	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = 0;
	if (hasendl(buf))
	{
		trim_buf(buf);
		line = complete_line(line, buf);
		if (!line)
			return (NULL);
	}
	while (!hasendl(buf))
	{
		line = read_and_complete(line, buf, fd, &bytes_read);
		if (!line)
			return (NULL);
		if ((bytes_read > 0 && bytes_read < BUFFER_SIZE) || !bytes_read)
			return (line);
	}
	return (line);
}

//ugly
