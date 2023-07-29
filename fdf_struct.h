/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 04:19:47 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/29 15:03:26 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCT_H
# define FDF_STRUCT_H

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
	int					**map_z;
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

#endif
