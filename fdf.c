/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:03:13 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/26 03:03:39 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pos	init_pos(int x1, int y1, int x2, int y2)
{
	t_pos	pos;

	pos.x1 = x1;
	pos.y1 = y1;
	pos.x2 = x2;
	pos.y2 = y2;
	pos.dx = x2 - x1;
	pos.dy = y2 - y1;
	pos.x_step = 1;
	pos.y_step = 1;
	pos.x1_v = x1;
	pos.y1_v = y1;
	pos.x2_v = x2;
	pos.y2_v = y2;
	return (pos);
}

void	draw(t_vars *vars)
{
	int		i;
	int		j;
	t_pos	pos;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			if (i + 1 < vars->height)
			{
				pos = init_pos(j, i, j, i + 1);
				bresenham(&pos, vars);
			}
			if (j + 1 < vars->width)
			{
				pos = init_pos(j, i, j + 1, i);
				bresenham(&pos, vars);
			}
			j++;
		}
		i++;
	}
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q fdf");
// }

int	main(int argc, char **argv)
{
	t_vars	*vars;

	if (argc != 2)
		exit(0);
	vars = malloc(sizeof(t_vars));
	if (vars == NULL)
		exit(1);
	prepare_map(argv[1], vars);
	prepare_mlx_vars(vars);
	calc_center_default(vars);
	set_default_param(vars);
	draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_key_hook(vars->win, catch_keycode, vars);
	mlx_hook(vars->win, DestroyNotify, StructureNotifyMask, close_by_red_btn,
		vars);
	mlx_loop(vars->mlx);
	return (0);
}
