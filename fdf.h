/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:05:36 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/26 03:00:55 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/XKBlib.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 800
# define ISOMETRIC 1
# define PARALLEL -1
# define WHITE 0x00FFFFFF

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
}						t_pos;

typedef struct s_map_list
{
	char				*row;
	struct s_map_list	*next;
}						t_map_list;

// bresenham.c
void					bresenham(t_pos *pos, t_vars *vars);

// mlx_utils1.c
void					my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
int						create_trgb(int t, int r, int g, int b);
void					reset_all_puts(t_vars *vars);
int						close_by_red_btn(t_vars *vars);

// mlx_utils2.x
void					set_default_param(t_vars *vars);
void					prepare_mlx_vars(t_vars *vars);
int						catch_keycode(int keycode, t_vars *vars);

//make_map1.c
void					prepare_map(char *filepath, t_vars *vars);

// make_map2.c
int						calc_height(t_map_list *head_map_list);
int						calc_width(t_map_list *head_map_list);
void					make_map(t_map_list *head_map_list, t_vars *vars);

// get_int_color_from_base16.c
int						get_color(char *cell);

// change_view.c
void					isometric(int *x, int *y, int *z);
void					parallel(int *x, int *y, int *z);
void					calc_rotate(t_pos *pos, t_vars *vars);
void					calc_scale(t_pos *pos, t_vars *vars);
void					calc_translate(t_pos *pos, t_vars *vars);

// change_view2.c
void					calc_origin_center(t_vars *vars);
void					calc_center_default(t_vars *vars);

// fdf.c
void					draw(t_vars *vars);

#endif