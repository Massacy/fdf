/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:32:49 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/25 05:12:20 by imasayos         ###   ########.fr       */
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

// void rotate(int *x, int *y, t_vars *vars)
// {
// 	int x_old;
// 	int y_old;
// 	double rad;

// 	x_old = *x;
// 	y_old = *y;
// 	rad = ((double)vars->angle/(double)360) * 2 * M_PI;
// 	x_old -= vars->x_center;
// 	y_old -= vars->y_center;
// 	// printf("rad : %f\n", rad);
// 	*x = x_old * cos(rad) - y_old * sin(rad);
// 	*y = x_old * sin(rad) + y_old * cos(rad);
// 	*x += vars->x_center;
// 	*y += vars->y_center;
// }

// int calc_center_img()
// {
// 	return (0);
// }

// void scale_all(t_pos *pos, t_vars *vars)
// {
// 	*x = *x * vars->zoom;
// 	*y = *y * vars->zoom;
// 	*z = *z * vars->zoom;
// }

// void scale_z(int *z, t_vars *vars)
// {
// 	*z = *z * vars->zoom_z;
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

void calc_rotate(t_pos *pos, t_vars *vars)
{
	int x_old;
	int y_old;
	double rad;

	// printf("before rotate x: : %d\n", pos->x1_v);
	// printf("before rotate y: : %d\n", pos->y1_v);
	x_old = pos->x1_v;
	y_old = pos->y1_v;
	rad = ((double)vars->angle/(double)360) * 2 * M_PI;
	x_old -= (vars->x_center * vars->base_zoom) * vars->zoom; //todo
	y_old -= (vars->y_center * vars->base_zoom) * vars->zoom; //todo
	// printf("rad : %f\n", rad);
	pos->x1_v = x_old * cos(rad) - y_old * sin(rad);
	pos->y1_v = x_old * sin(rad) + y_old * cos(rad);
	pos->x1_v += (vars->x_center * vars->base_zoom) * vars->zoom; //todo
	pos->y1_v += (vars->y_center * vars->base_zoom) * vars->zoom; //todo
	// printf("after rotate x: : %d\n", pos->x1_v);
	// printf("after rotate y: : %d\n", pos->y1_v);

	x_old = pos->x2_v;
	y_old = pos->y2_v;
	x_old -= (vars->x_center * vars->base_zoom) * vars->zoom; //todo
	y_old -= (vars->y_center * vars->base_zoom) * vars->zoom;
	pos->x2_v = x_old * cos(rad) - y_old * sin(rad);
	pos->y2_v = x_old * sin(rad) + y_old * cos(rad);
	pos->x2_v += (vars->x_center * vars->base_zoom) * vars->zoom; //todo
	pos->y2_v += (vars->y_center * vars->base_zoom) * vars->zoom;
}

void calc_scale(t_pos *pos, t_vars *vars)
{
	pos->x1_v = (pos->x1_v * vars->base_zoom) * vars->zoom;
	pos->y1_v = (pos->y1_v * vars->base_zoom) * vars->zoom;
	pos->x2_v = (pos->x2_v * vars->base_zoom) * vars->zoom;
	pos->y2_v = (pos->y2_v * vars->base_zoom) * vars->zoom;
	// pos->z1_v = pos->z1 * (vars->zoom + vars->zoom_z);
	// pos->z2_v = pos->z2 * (vars->zoom + vars->zoom_z);
	pos->z1 *= (vars->zoom_z * vars->zoom);
	pos->z2 *= (vars->zoom_z * vars->zoom);
}

void bresenham(t_pos *pos, t_vars *vars)
{

	pos->z1 = vars->map[pos->y1][pos->x1];
	pos->z2 = vars->map[pos->y2][pos->x2];
	// scale_all(pos, vars);
	// scale_all(&pos->x2, &pos->y2, &pos->z2, vars);
	// if (vars->zoom < 0)
	// 	vars->zoom = 0;
	// if (vars->zoom_z < 0)
	// 	vars->zoom_z = 0;
	

	// scale
	calc_scale(pos, vars);
	// rotate
	calc_rotate(pos, vars);

	
	// add_z(&pos->x1, &pos->y1, pos->z1, vars);
	// add_z(&pos->x2, &pos->y2, pos->z2, vars);
	
	// todo 戻す
	isometric(&pos->x1_v, &pos->y1_v, &pos->z1);
	isometric(&pos->x2_v, &pos->y2_v, &pos->z2);
	// printf("after x1 : %d, y1 : %d, z1 : %d\n", pos->x1, pos->y1, pos->z1);


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