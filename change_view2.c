/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_view2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:53:02 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/26 02:51:27 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_origin_center(t_vars *vars)
{
	vars->y_center = vars->height / 2;
	vars->x_center = vars->width / 2;
}

void	calc_center_default(t_vars *vars)
{
	int	x_min;
	int	x_max;
	int	y_min;
	int	y_max;

	x_min = (1 / sqrt(2)) * 0 - (1 / sqrt(2)) * vars->height;
	x_max = (1 / sqrt(2)) * vars->width - (1 / sqrt(2)) * 0;
	y_min = 0;
	y_max = (1 / sqrt(6)) * vars->width + (1 / sqrt(6)) * vars->height - (2
			/ sqrt(6)) * vars->map[vars->height - 1][vars->width - 1];
	if (WINDOW_WIDTH / (x_max - x_min) < WINDOW_HEIGHT / (y_max - y_min))
		vars->base_zoom = WINDOW_WIDTH / (x_max - x_min);
	else
		vars->base_zoom = WINDOW_HEIGHT / (y_max - y_min);
	vars->x_center_update = (x_min + (x_max - x_min) / 2) * vars->base_zoom;
	vars->y_center_update = (y_min + (y_max - y_min) / 2) * vars->base_zoom;
	vars->shift_x = WINDOW_WIDTH / 2 - vars->x_center_update;
	vars->shift_y = WINDOW_HEIGHT / 2 - vars->y_center_update;
}
