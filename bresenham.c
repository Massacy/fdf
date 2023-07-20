/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:32:49 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/21 02:42:05 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static int condition_by_direction(int a, int direction_a, int direction_sign)
{
	// printf("a1 : %d, a2 : %d, step: %d\n", a, direction_a, direction_sign);
	if (direction_sign > 0)
		return (a < direction_a);
	else
		return (a > direction_a);
}

// void swap_x_and_y(t_pos *pos)
// {
// 	int tmp;

// 	tmp = pos->x1;
// 	pos->x1 = pos->y1;
// 	pos->y1 = tmp;

// 	tmp = pos->x2;
// 	pos->x2 = pos->y2;
// 	pos->y2 = tmp;

// 	tmp = pos->dx;
// 	pos->dx = pos->dy;
// 	pos->dy = tmp;

// 	tmp = pos->x_step;
// 	pos->x_step = pos->y_step;
// 	pos->y_step = tmp;
// }




void add_z(int *x, int *y, int z, t_vars *vars)
{
	*x = (*x - *y) * cos(vars->angle);
	*y = (*x + *y) * sin(vars->angle) - z;
	// (void)z;
	// *y = (*x + *y) * sin(vars->angle);
}

// int trans_x(int x, int y, int z, t_vars *vars)
// {
// 	return ((x - y) * cos(vars->angle));
// }

// int trans_y(int x, int y, int z, t_vars *vars)
// {
// 	return (((x + y) * sin(vars->angle)) - z);
// }

static void loop_case_dx_gt_dy(t_pos *pos, t_vars *vars)
{
	int x;
	int y;
	int err;

	x = pos->x1;
	y = pos->y1;
	err = 0;
	while (condition_by_direction(x, pos->x2, pos->x_step))
	{
		if (err < pos->dx)
			err = err +(2 * pos->dy);
		else
		{
			err = err + (2 * (pos->dy - pos->dx));
			y = y + pos->y_step;
		}
		my_mlx_pixel_put(vars, x, y, vars->color);
		x = x + pos->x_step;
	}
}

static void loop_case_dx_lt_dy(t_pos *pos, t_vars *vars)
{
	int x;
	int y;
	int err;

	x = pos->x1;
	y = pos->y1;
	err = 0;
	while (condition_by_direction(y, pos->y2, pos->y_step))
	{
		if (err < pos->dy)
			err = err + (2 * pos->dx);
		else
		{
			err = err + (2 * (pos->dx - pos->dy));
			x = x + pos->x_step;
		}
		my_mlx_pixel_put(vars, x, y, vars->color);
		y = y + pos->y_step;
	}
}



void bresenham(t_pos *pos, t_vars *vars)
{
	int z1;
	int z2;

	z1 = vars->map[pos->y1][pos->x1];
	z2 = vars->map[pos->y2][pos->x2];

	pos->x1 *= vars->zoom;
	pos->y1 *= vars->zoom;
	pos->x2 *= vars->zoom;
	pos->y2 *= vars->zoom;
	pos->dx *= vars->zoom;
	pos->dy *= vars->zoom;

	add_z(&(pos->x1), &(pos->y1), z1, vars);
	add_z(&pos->x2, &pos->y2, z2, vars);
	
	// xとyが更新してからdxとdyの更新を忘れてた。(3d導入後これが起因のbug対応の時間がほとんどだった)
	pos->dx = pos->x2 - pos->x1;
	pos->dy = pos->y2 - pos->y1;

	pos->x1 += vars->shift_x;
	pos->y1 += vars->shift_y;
	pos->x2 += vars->shift_x;
	pos->y2 += vars->shift_y;


	if (pos->dx < 0)
	{
		pos->dx = -pos->dx;
		pos->x_step = -1;
	}
	if (pos->dy < 0)
	{
		pos->dy = -pos->dy;
		pos->y_step = -1;
	}
	// draw(pos, data, vars);
	if (pos->dx < pos->dy)
		loop_case_dx_lt_dy(pos, vars);
	else
		loop_case_dx_gt_dy(pos, vars);
}