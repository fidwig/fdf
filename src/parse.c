/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:23:39 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/15 20:16:43 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


char	*add_row_str(char *map_str, char *new_row)
{
	size_t	row_len;
	size_t	map_len;
	char	*new_map_str;

	map_len = 0;
	if (map_str)
		map_len = ft_strlen(map_str);
	row_len = ft_strlen(new_row);
	new_map_str = (char *)malloc((map_len + row_len + 1) * sizeof(char));
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

void	init_map_points(t_vars *vars)
{
	int	i;

	i = 0;
	vars->map.points = (t_pt **) malloc((vars->map.hei) * sizeof(t_pt *));
	vars->map.points_proj = (t_vec3 **) malloc((vars->map.hei) * sizeof(t_vec3 *));
	while (i < vars->map.hei)
	{
		vars->map.points[i] = (t_pt *)malloc((vars->map.wid) * sizeof(t_pt));
		vars->map.points_proj[i] = (t_vec3 *)malloc((vars->map.wid) * sizeof(t_vec3));
		i++;
	}
}

char	*read_map(int fd, t_vars *vars)
{
	char	*line;
	char	*map_str;

	map_str = NULL;
	line = get_next_line(fd);
	vars->map.wid = count_points(line, ' ');
	while (line)
	{
		vars->map.hei++;
		map_str = add_row_str(map_str, line);
		free(line);
		line = get_next_line(fd);
		if (line && count_points(line, ' ') != vars->map.wid)
			free_and_exit1(vars, line, map_str);
	}
	return (map_str);
}

t_pt	get_point_data(char *s, int x, int y, t_vars *vars)
{
	char	**pt_split;
	t_pt	point;

	pt_split = ft_split(s, ',');
	point.pos.x = x - vars->map.wid / 2;
	point.pos.y = y - vars->map.hei / 2;
	point.pos.z = ft_atoi(pt_split[0]);
	if (pt_split[1])
		point.col = (unsigned int) ft_atoui(&(pt_split[1][2]));
	else
		point.col = DEFAULT_COLOR;
	ft_free_split(pt_split);
	return (point);
}

void	parse_map(t_vars *vars, char *map_str)
{
	char	**map_split;
	char	**row_split;
	int		x;
	int		y;

	init_map_points(vars);
	map_split = ft_split(map_str, '\n');
	free(map_str);
	y = 0;
	while (map_split[y])
	{
		row_split = ft_split(map_split[y], ' ');
		x = 0;
		while (row_split[x])
		{
			vars->map.points[y][x] = get_point_data(row_split[x], x, y, vars);
			x++;
		}
		ft_free_split(row_split);
		y++;
	}
	ft_free_split(map_split);
}
