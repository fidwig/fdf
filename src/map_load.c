/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:23:39 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/26 16:59:01 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*add_row_str(t_vars *vars, char *map_str, char *new_row)
{
	size_t	row_len;
	size_t	map_len;
	char	*new_map_str;

	map_len = 0;
	if (map_str)
		map_len = ft_strlen(map_str);
	row_len = ft_strlen(new_row);
	new_map_str = (char *)malloc((map_len + row_len + 1) * sizeof(char));
	if (!new_map_str)
		free_and_exit2(vars, map_str, new_row);
	ft_memcpy(new_map_str, map_str, map_len);
	ft_memcpy(new_map_str + map_len, new_row, row_len);
	new_map_str[map_len + row_len] = 0;
	free(map_str);
	return (new_map_str);
}

int	count_points(char const *s, char c)
{
	int	l;
	int	i;

	i = 0;
	l = 0;
	while (s[i] && s[i] != '\n')
	{
		while (s[i] == c && s[i] && s[i] != '\n')
			i++;
		if (s[i] != c && s[i] && s[i] != '\n')
			l++;
		while (s[i] != c && s[i] && s[i] != '\n')
			i++;
	}
	return (l);
}

void	open_map(t_vars *vars, char *path)
{
	vars->fd = open(path, O_DIRECTORY);
	if (vars->fd != -1)
		close_and_exit(vars);
	vars->fd = open(path, O_RDONLY);
	if (vars->fd == -1)
		close_and_exit(vars);
	parse_map(vars, read_map(vars->fd, vars));
	close(vars->fd);
	vars->fd = -1;
}

char	*read_map(int fd, t_vars *vars)
{
	char	*line;
	char	*map_str;

	map_str = NULL;
	line = get_next_line(fd);
	if (!line)
		exit (1);
	vars->map.wid = count_points(line, ' ');
	while (line)
	{
		vars->map.hei++;
		map_str = add_row_str(vars, map_str, line);
		free(line);
		line = get_next_line(fd);
		if (line && count_points(line, ' ') != vars->map.wid)
			free_and_exit2(vars, line, map_str);
	}
	return (map_str);
}

void	parse_map(t_vars *vars, char *map_str)
{
	char	**map_split;
	char	**row_split;
	int		x;
	int		y;

	map_split = add_ptr_split(vars, ft_split(map_str, '\n'));
	free(map_str);
	if (!map_split)
		free_and_exit1(vars);
	init_map_points(vars);
	y = 0;
	while (map_split[y])
	{
		row_split = add_ptr_split(vars, ft_split(map_split[y], ' '));
		if (!row_split)
			free_and_exit1(vars);
		x = -1;
		while (row_split[++x])
			vars->map.points[y][x] = get_point_data(row_split[x], x, y, vars);
		free_ptr_split(vars, row_split);
		y++;
	}
	free_all(vars);
}
