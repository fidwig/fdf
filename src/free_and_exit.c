/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:24:16 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/15 16:59:00 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->map.hei)
	{
		free(vars->map.points[i]);
		free(vars->map.points_proj[i]);
		i++;
	}
	free(vars->map.points);
	free(vars->map.points_proj);
}

void	free_mlx(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}

void	free_and_exit1(t_vars *vars, void *line, void *map_str)
{
	free(line);
	free(map_str);
	free_mlx(vars);
	exit(1);
}
