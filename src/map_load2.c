/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:03:50 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/26 16:23:18 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map_points(t_vars *vars)
{
	int	i;

	i = 0;
	vars->map.points = (t_pt **) malloc((vars->map.hei) * sizeof(t_pt *));
	if (!vars->map.points)
		close_and_exit(vars);
	vars->map.points_proj = malloc((vars->map.hei) * sizeof(t_vec3 *));
	if (!vars->map.points_proj)
		free_and_exit2(vars, vars->map.points, NULL);
	while (i < vars->map.hei)
	{
		vars->map.points[i] = (t_pt *)malloc((vars->map.wid) * sizeof(t_pt));
		vars->map.points_proj[i] = malloc((vars->map.wid) * sizeof(t_vec3));
		if (!vars->map.points[i] || !vars->map.points_proj[i])
		{
			free(vars->map.points[i]);
			free(vars->map.points_proj[i]);
			vars->map.points[i] = NULL;
			vars->map.points_proj[i] = NULL;
			close_and_exit(vars);
		}
		i++;
	}
}

t_pt	get_point_data(char *s, int x, int y, t_vars *vars)
{
	char	**pt_split;
	t_pt	point;

	pt_split = ft_split(s, ',');
	if (!pt_split)
		free_and_exit1(vars);
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
