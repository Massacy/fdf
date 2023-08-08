/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:41:32 by imasayos          #+#    #+#             */
/*   Updated: 2023/08/08 20:54:21 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, t_pos *pos)
{
	char	*dst;

	if (0 <= x && x < WINDOW_WIDTH && 0 <= y && y < WINDOW_HEIGHT)
	{
		if (vars->map_z[y][x] < pos->z2)
			return ;
		vars->map_z[y][x] = pos->z2;
		dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = vars->map_color[pos->y2][pos->x2];
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	reset_all_puts(t_vars *vars)
{
	char	*dst;
	int		x;
	int		y;

	y = 0;
	while (y <= WINDOW_HEIGHT)
	{
		x = 0;
		while (x <= WINDOW_WIDTH)
		{
			dst = vars->addr + (y * vars->line_length + x
					* (vars->bits_per_pixel / 8));
			*(unsigned int *)dst = 0x00000000;
			x++;
		}
		y++;
	}
}

int	close_by_red_btn(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	exit(0);
}

void	prepare_mlx_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
	if (vars->mlx == NULL || vars->win == NULL || vars->img == NULL
		|| vars->addr == NULL)
		exit(1);
}

// int	close_by_esc(int keycode, t_vars *vars)
// {
// 	if (keycode == XK_Escape)
// 	{
// 		mlx_destroy_window(vars->mlx, vars->win);
// 		exit(0);
// 	}
// 	return (0);
// }
