/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:05:36 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/21 03:20:31 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

// #define KEY_A 97
// #define KEY_D 100
// #define KEY_S 115
// #define KEY_W 119
// #define KEY_I 105
// #define KEY_O 111

typedef struct s_vars
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	void	*mlx;
	void	*win;
	int		height;
	int		width;
	int		**map;
	int		color;
	int		zoom;
	double	angle;
	int		shift_x;
	int		shift_y;

}			t_vars;

typedef struct s_pos
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		dx;
	int		dy;
	int		x_step;
	int		y_step;
	int		z1;
	int		z2;
}			t_pos;

void		bresenham(t_pos *pos, t_vars *vars);

void		my_mlx_pixel_put(t_vars *vars, int x, int y, int color);

#endif