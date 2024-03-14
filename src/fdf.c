/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:03:55 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/14 19:11:17 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	update(t_vars *vars)
{
	(void) vars;
	return (0);
}

void	draw_points_no_depth(t_vars *vars)
{
	int					y;
	int					x;
	t_pt				**pts;
	t_pt				scsp;

	pts = vars->map.points;
	y = 0;
	while (y < vars->map.hei)
	{
		x = 0;
		while (x < vars->map.wid)
		{
			scsp = get_screenspace_pos(vars, pts[y][x]);
			if (scsp.pos.x > WIDTH + 100 || scsp.pos.y > HEIGHT + 100 || scsp.pos.x < -100 || scsp.pos.y < -100)
			{
				x++;
				continue ;
			}
			if (x < vars->map.wid - 1)
				draw_line(vars, scsp, get_screenspace_pos(vars, pts[y][x + 1]));
			if (y < vars->map.hei - 1)
				draw_line(vars, scsp, get_screenspace_pos(vars, pts[y + 1][x]));
			pixel_put(&vars->img, scsp.pos.x, scsp.pos.y, scsp.col);
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

int	close_all(t_vars *vars)
{
	free_mlx(vars);
	free_map(vars);
	exit (0);
}

void	refresh_image(t_vars *vars)
{
	clear_image(&vars->img, BLACK);
	draw_points_no_depth(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

void	update_depth(int change, t_vars *vars)
{
	vars->transform.depth_scale += change * 0.01;
	refresh_image(vars);
}

void	update_zoom(int change, t_vars *vars)
{
	vars->transform.scale += change * 0.1;
	refresh_image(vars);
}

void	move_grid(int x, int y, t_vars *vars)
{
	vars->transform.offset.x += x * 5;
	vars->transform.offset.y += y * 5;
	refresh_image(vars);
}

void	rotate_grid_z(int rotation, t_vars *vars)
{
	vars->transform.rotations.z += rotation;
	refresh_image(vars);
}

void	rotate_grid_x(int rotation, t_vars *vars)
{
	vars->transform.rotations.x += rotation;
	refresh_image(vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		close_all(vars);
	update_depth((keycode == XK_x) - (keycode == XK_z), vars);
	update_zoom((keycode == XK_v) - (keycode == XK_c), vars);
	move_grid((keycode == XK_d) - (keycode == XK_a), (keycode == XK_s) - (keycode == XK_w), vars);
	rotate_grid_x((keycode == XK_Up) - (keycode == XK_Down), vars);
	rotate_grid_z((keycode == XK_Right) - (keycode == XK_Left), vars);
	return (0);
}

void	init_transform(t_vars *vars)
{
	vars->transform.scale = SCALE;
	vars->transform.depth_scale = DEPTH_SCALE;
	vars->transform.offset = (t_vec3){CENTER_X, CENTER_Y, 0};
	vars->transform.rotations = (t_vec3){50, 0, 45};
	vars->transform.prev_rots = (t_vec3){0, 0, 0};
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
	init_transform(&vars);
	if (!vars.mlx || !vars.win)
		return (1);
	fd = open(argv[1], O_RDONLY);
	parse_map(&vars, read_map(fd, &vars));
	close(fd);
	draw_points_no_depth(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_loop_hook(vars.mlx, update, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_loop(vars.mlx);
}
