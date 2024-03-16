/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:03:55 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/16 03:46:54 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project_points(t_vars *vars)
{
	int		x;
	int		y;
	t_vec3	p_pos;

	if (!vars->transform.project)
		return ;
	y = 0;
	while (y < vars->map.hei)
	{
		x = 0;
		while (x < vars->map.wid)
		{
			p_pos = project_pos(vars, vars->map.points[y][x].pos);
			if (y + x == 0 || p_pos.z > vars->map.clo)
				vars->map.clo = p_pos.z;
			if (y + x == 0 || p_pos.z < vars->map.fur)
				vars->map.fur = p_pos.z;
			vars->map.points_proj[y][x] = p_pos;
			x++;
		}
		y++;
	}
}

int	is_on_display(t_vec3 pos)
{
	return (pos.x < WIDTH && pos.y < HEIGHT
		&& pos.x > 0 && pos.y > 0);
}

void	draw_projected_points(t_vars *vars)
{
	int					y;
	int					x;
	t_pt				pt;
	t_pt				apt;

	y = 0;
	while (y < vars->map.hei)
	{
		x = 0;
		while (x < vars->map.wid)
		{
			pt = get_transformed_point(vars, x, y);
			if (x < vars->map.wid - 1)
			{
				apt = get_transformed_point(vars, x + 1, y);
				if (is_on_display(pt.pos) || is_on_display(apt.pos))
					draw_line(vars, pt, apt);
			}
			if (y < vars->map.hei - 1)
			{
				apt = get_transformed_point(vars, x, y + 1);
				if (is_on_display(pt.pos) || is_on_display(apt.pos))
					draw_line(vars, pt, apt);
			}
			x++;
		}
		y++;
	}
}

void	clear_image(t_data *image, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			pixel_put(image, i, j, color);
			j++;
		}
		i++;
	}
}

void	refresh_image(t_vars *vars)
{
	clear_image(&vars->img, BLACK);
	project_points(vars);
	draw_projected_points(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}


void	init_transform(t_vars *vars)
{
	vars->transform.scale = HEIGHT / vars->map.hei;
	vars->transform.depth_scale = DEPTH_SCALE;
	vars->transform.offset = (t_vec3){OFFSET_X, OFFSET_Y, 0};
	vars->transform.rotations = (t_vec3){50, 0, 45};
	vars->transform.rotate = 1;
	vars->transform.project = 1;
}

int	update(t_vars *vars)
{
	refresh_image(vars);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		fd;

	if (argc != 2)
		return (1);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "FUCK YOU");
	vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bit_depth,
			&vars.img.line_length, &vars.img.endian);
	vars.map = (t_map){0};
	if (!vars.mlx || !vars.win)
		return (1);
	fd = open(argv[1], O_RDONLY);
	parse_map(&vars, read_map(fd, &vars));
	close(fd);
	init_transform(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_loop_hook(vars.mlx, update, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_loop(vars.mlx);
}
