/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:51:19 by imasayos          #+#    #+#             */
/*   Updated: 2023/08/03 20:45:03 by imasayos         ###   ########.fr       */
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
	refresh_map_z(vars);
	draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

void	create_init_map_z(t_vars *vars)
{
	int	**map_z;
	int	i;
	int	j;

	map_z = init_map_area(WINDOW_HEIGHT, WINDOW_WIDTH);
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			map_z[i][j] = INT_MAX;
			j++;
		}
		i++;
	}
	vars->map_z = map_z;
}

void	set_default_param(t_vars *vars)
{
	vars->zoom = 1;
	vars->zoom_z = 1;
	vars->angle = 0;
	vars->is_isometric = 1;
	vars->color = create_trgb(0, 255, 255, 255);
	create_init_map_z(vars);
}
