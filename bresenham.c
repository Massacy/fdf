/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:32:49 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/19 03:24:12 by imasayos         ###   ########.fr       */
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


static void loop_case_dx_gt_dy(t_pos *pos, t_data *data, t_vars *vars)
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
			err = err + 2 * pos->dy;
		else
		{
			err = err + 2 * (pos->dy - pos->dx);
			y = y + pos->y_step;
		}
		(void)vars;
		// printf("x : %d, y : %d\n", x, y);
		my_mlx_pixel_put(data, x, y, vars->color);
		x = x + pos->x_step;
	}
}

static void loop_case_dx_lt_dy(t_pos *pos, t_data *data, t_vars *vars)
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
			err = err + 2 * pos->dx;
		else
		{
			err = err + 2 * (pos->dx - pos->dy);
			x = x + pos->x_step;
		}
		(void)vars;
		my_mlx_pixel_put(data, x, y, vars->color);

		y = y + pos->y_step;
	}
}




void bresenham(t_pos *pos, t_data *data, t_vars *vars)
{
	// int err;
	// int x;
	// int y;

	// (1)
	// x = pos->x1;
	// y = pos->y1;
	// (2)


	pos->x1 *= vars->zoom;
	pos->y1 *= vars->zoom;
	pos->y2 *= vars->zoom;
	pos->x2 *= vars->zoom;

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
	if (pos->dx < pos->dy)
		loop_case_dx_lt_dy(pos, data, vars);
	else
		loop_case_dx_gt_dy(pos, data, vars);
}