/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:03:13 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/20 04:26:04 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
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


// int	count_word(char const *s, char c)
// {
// 	int	cnt;
// 	int	i;

// 	cnt = 0;
// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		if ((i == 0 || (i > 0 && s[i - 1] == c)) && s[i] != c)
// 			cnt++;
// 		i++;
// 	}
// 	return (cnt);
// }

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
	printf("gnl : %s\n", gnl);
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

// void check_gnl(char *filepath)
// {
// 	char *gnl;
// 	int fd;

// 	fd = open(filepath, O_RDONLY);
// 	gnl = get_next_line(fd);
// 	free(gnl);
// 	close(fd);
// }

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}



void put_5pics(int x, int y, int num,t_data *img)
{
	int i;
	int j;
	int color;

	color = create_trgb(0, num, 0, 0);
	i = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			my_mlx_pixel_put(img, 20*x + i, 20*y + j, color);
			j++;
		}
		i++;
	}
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

void draw_sample(t_vars *vars, t_data *image, int **map)
{
	int i;
	int j;
	int color;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			if (map[i][j] == 0)
				color = create_trgb(0, 0, 0, 255);
			else
				color = create_trgb(0, 255, 0, 0);
			put_5pics(j, i, color, image);
			j++;
		}
		i++;
	}
}

void draw_sample2(t_vars *vars, t_data *data)
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
			
			if (vars->map[i][j] == 0)
				vars->color = create_trgb(0, 255, 255, 255);
			else
				vars->color = create_trgb(0, 0, 255, 0);
			if (i+1 < vars->height)
			{
				pos = init_pos(j, i, j, i+1);
				bresenham(&pos, data, vars);
			}
			if (j + 1 < vars->width)
			{
				pos = init_pos(j, i, j+1, i);
				bresenham(&pos, data, vars);
			}
			j++;
		}
		i++;
	}
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q fdf");
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_data	img;
	int **map;

	if (argc != 2)
		exit(0);
	(void)argc;
	(void)argv;
	(void)map;

	vars.height = calc_height(argv[1]);
	vars.width = calc_width(argv[1]);
	printf("height: %d\n", vars.height);
	printf("width: %d\n", vars.width);
	map = make_map(argv[1], vars.height, vars.width);

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 800, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1000, 800);
	
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000); // red
	// my_mlx_pixel_put(&img, 10, 10, 0x0000FF00); // green
	// my_mlx_pixel_put(&img, 15, 15, 0x000000FF); // blue

	// draw_sample(&vars, &img, map);
	vars.map = map;
	vars.zoom = 20;
	vars.angle = 0.8;
	// vars.color = create_trgb(0, 255, 0, 0);
	draw_sample2(&vars, &img);
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


	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_by_red_btn, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, close_by_esc, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
