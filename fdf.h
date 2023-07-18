/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:05:36 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/19 03:11:27 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <math.h>
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>

#include <stdio.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int 	height;
	int 	width;
	int		**map;
	int		color;
	int zoom;

}			t_vars;

typedef struct s_pos
{
	int x1;
	int y1;
	int x2;
	int y2;
	int dx;
	int dy;
	int x_step;
	int y_step;
} t_pos;

void bresenham(t_pos *pos, t_data *data, t_vars *vars);

void my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif