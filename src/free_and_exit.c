/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:24:16 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/27 16:09:43 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_vars *vars)
{
	int	i;

	if (vars->map.points)
	{
		i = 0;
		while (i < vars->map.hei && vars->map.points[i])
			free(vars->map.points[i++]);
		free(vars->map.points);
	}
	if (vars->map.points_proj)
	{
		i = 0;
		while (i < vars->map.hei && vars->map.points_proj[i])
			free(vars->map.points_proj[i++]);
		free(vars->map.points_proj);
	}
}

void	free_mlx(t_vars *vars)
{
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}

void	free_and_exit2(t_vars *vars, void *ptr, void *ptr2)
{
	free(ptr);
	free(ptr2);
	free_all(vars);
	if (vars->fd != -1)
		close(vars->fd);
	exit(1);
}
	// write(2, "Lines length do not match\n", 26);

void	free_and_exit1(t_vars *vars)
{
	if (vars->fd != -1)
		close(vars->fd);
	free_all(vars);
	free_map(vars);
	exit(1);
}

void	close_and_exit(t_vars *vars)
{
	free_map(vars);
	free_all(vars);
	if (vars->fd != -1)
		close(vars->fd);
	vars->display_mode = write(2, "I dont like the path you gave me\n", 38);
	exit (1);
}
