/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:41:32 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/26 02:43:46 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	if (0 <= x && x < WINDOW_WIDTH && 0 <= y && y < WINDOW_HEIGHT)
	{
		dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
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
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
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
