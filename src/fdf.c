/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:03:55 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/26 15:14:01 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int	is_on_display(t_vec3 pos)
// {
// 	return (pos.x < WIDTH && pos.y < HEIGHT
// 		&& pos.x > 0 && pos.y > 0);
// }

int	out_of_display(float x, float y, float cx, float cy)
{
	if (x < 0 && cx < 0)
		return (1);
	if (y < 0 && cy < 0)
		return (1);
	if (x > WIDTH && cx > 0)
		return (1);
	if (y > HEIGHT && cy > 0)
		return (1);
	return (0);
}

void	refresh_image(t_vars *vars)
{
	clear_image(&vars->img, BLACK);
	project_points(vars);
	draw_projected_points(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

void	init_values(t_vars *vars)
{
	float	len;

	len = sqrt(vars->map.hei * vars->map.hei + vars->map.wid * vars->map.wid);
	vars->transform.scale = (HEIGHT / len) * 1.5;
	vars->transform.depth_scale = DEPTH_SCALE;
	vars->transform.offset = (t_vec3){0, 0, 0};
	vars->transform.rotations = (t_vec3){50, 0, 45};
	vars->transform.rotate = 1;
	vars->transform.project = 1;
	vars->cam.fov = 2;
	vars->cam.far = -vars->cam.fov * (vars->map.hei + vars->map.wid);
	vars->cam.near = 0;
}

int	update(t_vars *vars)
{
	refresh_image(vars);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		return (1);
	vars = (t_vars){0};
	open_map(&vars, argv[1]);
	init_values(&vars);
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, argv[1]);
	if (!vars.win)
	{
		free_and_exit1(&vars);
		return (1);
	}
	vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bit_depth,
			&vars.img.line_length, &vars.img.endian);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_loop_hook(vars.mlx, update, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_loop(vars.mlx);
}
