/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 05:27:48 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/25 23:17:47 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void parallel(int *x, int *y, int *z)
{
	int x_old;
	int y_old;
	int z_old;

	x_old = *x;
	y_old = *y;
	z_old = *z;
	*x = (sqrt(6) / 3) * x_old - (sqrt(3) / 3) * y_old;
	*y = (sqrt(3)/3) * y_old - (sqrt(6)/3) * z_old;
	*z = -(1/2)*x_old -(sqrt(2)/2) *y_old -(1/2)*z_old;
}

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
