/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:32:49 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/26 02:56:46 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	condition_by_direction(int a, int direction_a, int direction_sign)
{
	if (direction_sign > 0)
		return (a < direction_a);
	else
		return (a > direction_a);
}

static void	loop_case_dx_gt_dy(t_pos *pos, t_vars *vars)
{
	int	x;
	int	y;
	int	err;

	x = pos->x1_v;
	y = pos->y1_v;
	err = 0;
	while (condition_by_direction(x, pos->x2_v, pos->x_step))
	{
		if (err < pos->dx_v)
			err = err + (2 * pos->dy_v);
		else
		{
			err = err + (2 * (pos->dy_v - pos->dx_v));
			y = y + pos->y_step;
		}
		my_mlx_pixel_put(vars, x, y, vars->map_color[pos->y2][pos->x2]);
		x = x + pos->x_step;
	}
}

static void	loop_case_dx_lt_dy(t_pos *pos, t_vars *vars)
{
	int	x;
	int	y;
	int	err;

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
		y = y + pos->y_step;
	}
}

static void	select_projection(t_pos *pos, t_vars *vars)
{
	if (vars->is_isometric == ISOMETRIC)
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
}

void	bresenham(t_pos *pos, t_vars *vars)
{
	pos->z1 = vars->map[pos->y1][pos->x1];
	pos->z2 = vars->map[pos->y2][pos->x2];
	calc_scale(pos, vars);
	calc_rotate(pos, vars);
	select_projection(pos, vars);
	calc_translate(pos, vars);
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
