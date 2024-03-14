/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:42:38 by jsommet           #+#    #+#             */
/*   Updated: 2023/12/15 20:02:28 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		hasendl(char *s);
void	trim_buf(char *buf);
char	*complete_line(char *s, char *buf);
char	*read_and_complete(char *line, char *buf, int fd, ssize_t *bytes_read);

char	*get_next_line(int fd);

#endif
