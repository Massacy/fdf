/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:05:36 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/25 23:21:21 by imasayos         ###   ########.fr       */
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
# define ISOMETRIC 1
# define PARALLEL 2

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
	double				base_zoom;
	double				zoom;
	double				zoom_z;
	int					angle;
	int					shift_x;
	int					shift_y;
	int					x_center;
	int					y_center;
	int					x_center_update;
	int					y_center_update;

	int					is_isometric;

}						t_vars;

typedef struct s_pos
{
	int					x1;
	int					y1;
	int					x2;
	int					y2;
	int					x1_v;
	int					y1_v;
	int					x2_v;
	int					y2_v;

	int					dx;
	int					dy;
	int					dx_v;
	int					dy_v;
	int					x_step;
	int					y_step;
	int					z1;
	int					z2;
	// int					z1_v;
	// int					z2_v;
}						t_pos;

typedef struct s_map_list
{
	char				*row;
	struct s_map_list	*next;
}						t_map_list;

void					bresenham(t_pos *pos, t_vars *vars);

void					my_mlx_pixel_put(t_vars *vars, int x, int y, int color);

int						get_int_color_from_base16(char *nptr);

void					isometric(int *x, int *y, int *z);
void					parallel(int *x, int *y, int *z);
void					calc_rotate(t_pos *pos, t_vars *vars);
void					calc_scale(t_pos *pos, t_vars *vars);
#endif