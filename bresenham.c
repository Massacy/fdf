/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:32:49 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/25 22:19:21 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static int condition_by_direction(int a, int direction_a, int direction_sign)
{
	if (direction_sign > 0)
		return (a < direction_a);
	else
		return (a > direction_a);
}


// void add_z(int *x, int *y, int z, t_vars *vars)
// {
// 	*x = (*x - *y) * cos(vars->angle);
// 	*y = (*x + *y) * sin(vars->angle) - z;
// }


static void loop_case_dx_gt_dy(t_pos *pos, t_vars *vars)
{
	int x;
	int y;
	int err;

	x = pos->x1_v;
	y = pos->y1_v;
	err = 0;
	while (condition_by_direction(x, pos->x2_v, pos->x_step))
	{
		if (err < pos->dx_v)
			err = err +(2 * pos->dy_v);
		else
		{
			err = err + (2 * (pos->dy_v - pos->dx_v));
			y = y + pos->y_step;
		}
		// my_mlx_pixel_put(vars, x, y, vars->color);
		my_mlx_pixel_put(vars, x, y, vars->map_color[pos->y2][pos->x2]);

		x = x + pos->x_step;
	}
}

static void loop_case_dx_lt_dy(t_pos *pos, t_vars *vars)
{
	int x;
	int y;
	int err;

	x = pos->x1_v;
	y = pos->y1_v;
	err = 0;
	while (condition_by_direction(y, pos->y2_v, pos->y_step))
	{
		if (err < pos->dy_v)
			err = err + (2 * pos->dx_v);
		else
		{
			err = err + (2 * (pos->dx_v - pos->dy_v));
			x = x + pos->x_step;
		}
		my_mlx_pixel_put(vars, x, y, vars->map_color[pos->y2][pos->x2]);
		// my_mlx_pixel_put(vars, x, y, vars->color);

		y = y + pos->y_step;
	}
}

// static void print_pos(t_pos *pos)
// {
// 	printf("x1 : %d, y1 : %d, x2 : %d, y2 : %d\n", pos->x1, pos->y1, pos->x2, pos->y2);
// 	printf("x1_v : %d, y1_v : %d, x2_v : %d, y2_v : %d\n", pos->x1_v, pos->y1_v, pos->x2_v, pos->y2_v);
// 	printf("dx : %d, dy : %d, dx_v : %d, dy_v : %d\n", pos->dx, pos->dy, pos->dx_v, pos->dy_v);
// 	printf("x_step : %d, y_step : %d\n", pos->x_step, pos->y_step);
// 	printf("z1 : %d, z2 : %d\n", pos->z1, pos->z2);
// }



void bresenham(t_pos *pos, t_vars *vars)
{

	pos->z1 = vars->map[pos->y1][pos->x1];
	pos->z2 = vars->map[pos->y2][pos->x2];
	calc_scale(pos, vars);
	calc_rotate(pos, vars);
	if (vars->is_isometric == 1)
	{
		isometric(&pos->x1_v, &pos->y1_v, &pos->z1);
		isometric(&pos->x2_v, &pos->y2_v, &pos->z2);
	}
	else
	{
		parallel(&pos->x1_v, &pos->y1_v, &pos->z1);
		parallel(&pos->x2_v, &pos->y2_v, &pos->z2);
	}
	pos->dx_v = pos->x2_v - pos->x1_v;
	pos->dy_v = pos->y2_v - pos->y1_v;

	// translate
	pos->x1_v += vars->shift_x;
	pos->y1_v += vars->shift_y;
	pos->x2_v += vars->shift_x;
	pos->y2_v += vars->shift_y;

	if (pos->dx_v < 0)
	{
		pos->dx_v = -pos->dx_v;
		pos->x_step = -1;
	}
	if (pos->dy_v < 0)
	{
		pos->dy_v = -pos->dy_v;
		pos->y_step = -1;
	}
	if (pos->dx_v < pos->dy_v)
		loop_case_dx_lt_dy(pos, vars);
	else
		loop_case_dx_gt_dy(pos, vars);
}