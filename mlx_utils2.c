/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:51:19 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/26 02:43:23 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	move(int keycode, t_vars *vars)
{
	if (keycode == XK_Up || keycode == XK_w)
		vars->shift_y -= 20;
	if (keycode == XK_Down || keycode == XK_s)
		vars->shift_y += 20;
	if (keycode == XK_Right || keycode == XK_d)
		vars->shift_x += 20;
	if (keycode == XK_Left || keycode == XK_a)
		vars->shift_x -= 20;
}

static void	zoom_in_out(int keycode, t_vars *vars)
{
	if (keycode == XK_i)
		vars->zoom += 0.1;
	if (keycode == XK_o)
		vars->zoom -= 0.1;
	if (keycode == XK_j)
		vars->zoom_z += 1;
	if (keycode == XK_k)
		vars->zoom_z -= 1;
}

int	catch_keycode(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	move(keycode, vars);
	zoom_in_out(keycode, vars);
	if (keycode == XK_n)
		vars->angle = (vars->angle + 20 + 360) % 360;
	if (keycode == XK_m)
		vars->angle = (vars->angle - 20 + 360) % 360;
	if (keycode == XK_c)
		vars->is_isometric *= -1;
	reset_all_puts(vars);
	draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

void	set_default_param(t_vars *vars)
{
	vars->zoom = 1;
	vars->zoom_z = 1;
	vars->angle = 0;
	vars->is_isometric = 1;
	vars->color = create_trgb(0, 255, 255, 255);
}

void	prepare_mlx_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
}
