/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:03:13 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/21 03:25:31 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>


void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_by_red_btn(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	close_by_esc(int keycode, t_vars *vars)
{
	// KeySym keysym;
	// keysym = XkbKeycodeToKeysym(vars.mlx, keycode, 0, 0);
	// keysym = XKeycodeToKeysym(vars.mlx, keycode, 0);
	// printf("keysym: %lu\n", keysym);
	printf("keycode : %d\n", keycode);
	printf("XK_Escape : %d\n", XK_Escape);
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int calc_height(char *filepath)
{
	int height;
	int fd;
	char *gnl;

	height = 0;
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit(1);
	gnl = get_next_line(fd);	
	while (gnl != NULL)
	{
		height++;
		free(gnl);
		gnl = get_next_line(fd);
	}
	free(gnl);
	close(fd);
	return (height);
}

int calc_width(char *filepath)
{
	int width;
	char *gnl;
	int fd;
	char **split;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit(1);
	gnl = get_next_line(fd);
	split = ft_split(gnl, ' ');
	width = 0;
	while (split[width] != NULL)
		width++;
	free_split(split);
	free(gnl);
	close(fd);
	return (width);
}

int **init_map_area(int height, int width)
{
	int **map;
	int i;

	map = (int **)malloc(sizeof(int *) * height+1);
	if (map == NULL)
		exit(1);
	i = 0;
	while (i < height)
	{
		map[i] = (int *)malloc(sizeof(int) * width+1);
		if (map[i] == NULL)
			exit(1);
		i++;
	}
	return (map);
}

int **make_map(char *filepath, int height, int width)
{
	int **map;
	int fd;
	char *gnl;
	char **split;
	int i;
	int j;

	map = init_map_area(height, width);
	// TODO 
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit(1);
	i = 0;
	while (i < height)
	{
		gnl = get_next_line(fd);
		split = ft_split(gnl, ' ');
		j = 0;
		while (j < width)
		{
			map[i][j] = ft_atoi(split[j]);
			j++;
		}
		free_split(split);
		free(gnl);
		i++;
	}
	close(fd);
	return (map);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_pos init_pos(int x1, int y1, int x2, int y2)
{
	t_pos pos;

	pos.x1 = x1;
	pos.y1 = y1;
	pos.x2 = x2;
	pos.y2 = y2;
	pos.dx = x2 - x1;
	pos.dy = y2 - y1;
	pos.x_step = 1;
	pos.y_step = 1;
	return (pos);
}

void draw(t_vars *vars)
{
	int i;
	int j;
	t_pos pos;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			// TODO 色の設定法則考える
			if (vars->map[i][j] == 0)
				vars->color = create_trgb(0, 255, 255, 255);
			else
				vars->color = create_trgb(0, 0, 255, 0);
			if (i+1 < vars->height)
			{
				pos = init_pos(j, i, j, i+1);
				bresenham(&pos, vars);
			}
			if (j + 1 < vars->width)
			{
				pos = init_pos(j, i, j+1, i);
				bresenham(&pos, vars);
			}
			j++;
		}
		i++;
	}
}

int catch_keycode(int keycode, t_vars *vars)
{
	printf("keycode : %d\n", keycode);
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == XK_Up || keycode == XK_w)
		vars->shift_y -= 10;
	if (keycode == XK_Down || keycode == XK_s)
		vars->shift_y += 10;
	if (keycode == XK_Right || keycode == XK_d)
		vars->shift_x += 10;
	if (keycode == XK_Left || keycode == XK_a)
		vars->shift_x -= 10;
	if (keycode == XK_i)
		vars->zoom += 1;
	if (keycode == XK_o)
		vars->zoom -= 1;
	if (keycode == XK_j)
	{
		// TODO 一定以上でabortするの回避
		vars->angle += 0.1;
		printf("%f\n", vars->angle);
	}
	if (keycode == XK_k)
	{
		// TODO 一定以上でabortするの回避
		vars->angle -= 0.1;
	}
	// TODO 
	// mlx_clear_window(vars->mlx, vars->win);
	// mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q fdf");
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		exit(0);
	vars.height = calc_height(argv[1]);
	vars.width = calc_width(argv[1]);
	vars.map = make_map(argv[1], vars.height, vars.width);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 800, "Hello world!");
	vars.img = mlx_new_image(vars.mlx, 1000, 800);
	// vars.img_null = mlx_new_image(vars.mlx, 1000, 800);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length,
								 &vars.endian);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000); // red
	// my_mlx_pixel_put(&img, 10, 10, 0x0000FF00); // green
	// my_mlx_pixel_put(&img, 15, 15, 0x000000FF); // blue
	vars.zoom = 20;
	vars.angle = 0.8;
	vars.shift_x = 300;
	vars.shift_y = 200;
	// vars.color = create_trgb(0, 255, 0, 0);

	// t_pos pos;
	// printf("1");
	// pos = init_pos(0, 0, 100, 200);
	// bresenham(&pos, &img, &vars);
	// printf("2");
	// pos = init_pos(0, 0, 200, 100);
	// bresenham(&pos, &img, &vars);
	// printf("3");
	// pos = init_pos(0, 0, -100, 200);
	// bresenham(&pos, &img, &vars);
	// printf("4");
	// pos = init_pos(0, 0, -200, 100);
	// bresenham(&pos, &img, &vars);
	// printf("5");
	// pos = init_pos(0, 0, 100, -200);
	// bresenham(&pos, &img, &vars);
	// printf("6");
	// pos = init_pos(0, 0, 200, -100);
	// bresenham(&pos, &img, &vars);
	// printf("7");
	// pos = init_pos(0, 0, -100, -200);
	// bresenham(&pos, &img, &vars);
	// printf("8");
	// pos = init_pos(0, 0, -200, -100);
	// bresenham(&pos, &img, &vars);

	draw(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_key_hook(vars.win, catch_keycode, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_by_red_btn, &vars);
	// mlx_hook(vars.win, KeyPress, KeyPressMask, close_by_esc, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
