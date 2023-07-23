/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:32:49 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/23 12:26:47 by imasayos         ###   ########.fr       */
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


void add_z(int *x, int *y, int z, t_vars *vars)
{
	*x = (*x - *y) * cos(vars->angle);
	*y = (*x + *y) * sin(vars->angle) - z;
}

void isometric(int *x, int *y, int *z)
{
	int x_old;
	int y_old;
	int z_old;

	x_old = *x;
	y_old = *y;
	z_old = *z;
	*x =  (1 / sqrt(2)) * x_old - (1 / sqrt(2)) * y_old;
	*y =  (1 / sqrt(6)) * x_old + (1 / sqrt(6)) * y_old - (2/sqrt(6)) * z_old;
	*z = -(1 / sqrt(3)) * x_old - (1 / sqrt(3)) * y_old - (1/sqrt(3)) * z_old;
}

void scale()
{
	// int x;
	// int y;
	// int z;

	// x = pos->x1;
	// y = pos->y1;
	// z = vars->map[y][x];
	
}

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

	pos->z1 = vars->map[pos->y1][pos->x1];
	pos->z2 = vars->map[pos->y2][pos->x2];

	pos->x1 *= vars->zoom;
	pos->y1 *= vars->zoom;
	pos->x2 *= vars->zoom;
	pos->y2 *= vars->zoom;

	// add_z(&pos->x1, &pos->y1, pos->z1, vars);
	// add_z(&pos->x2, &pos->y2, pos->z2, vars);
	// printf("before x1 : %d, y1 : %d, z1 : %d\n", pos->x1, pos->y1, pos->z1);
	isometric(&pos->x1, &pos->y1, &pos->z1);
	// printf("after x1 : %d, y1 : %d, z1 : %d\n", pos->x1, pos->y1, pos->z1);
	isometric(&pos->x2, &pos->y2, &pos->z2);
	
	// xとyが更新してから(add_z適用後)dxとdyの更新を忘れてた。(3d導入後これが起因のbug対応の時間がほとんどだった)
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