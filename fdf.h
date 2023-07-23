/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:05:36 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/23 21:20:40 by imasayos         ###   ########.fr       */
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
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 800

typedef struct s_vars
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;

	void				*mlx;
	void				*win;
	int					height;
	int					width;
	int					**map;
	int					**map_color;
	int					color;
	int					zoom;
	double				angle;
	int					shift_x;
	int					shift_y;

}						t_vars;

typedef struct s_pos
{
	int					x1;
	int					y1;
	int					x2;
	int					y2;
	int					dx;
	int					dy;
	int					x_step;
	int					y_step;
	int					z1;
	int					z2;
}						t_pos;

typedef struct s_map_list
{
	char				*row;
	struct s_map_list	*next;
}						t_map_list;

void					bresenham(t_pos *pos, t_vars *vars);

void					my_mlx_pixel_put(t_vars *vars, int x, int y, int color);

#endif