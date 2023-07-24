/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:03:13 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/25 05:16:01 by imasayos         ###   ########.fr       */
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

	if (0 <= x && x < WINDOW_WIDTH && 0 <= y && y < WINDOW_HEIGHT)
	{
		dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	// printf("line_length : %d\n", vars->line_length);
	// printf("bits_per_pixel : %d\n", vars->bits_per_pixel);
	// printf("y_plus : %d\n", y * vars->line_length);
	// printf("x_plus : %d\n", x * (vars->bits_per_pixel / 8));
	// int i = -1;
	// while (++i < 4)
	// 	printf("dst before%d: %s\n", i+1, dst+i);
		*(unsigned int *)dst = color;
	// i = -1;
	// while (++i < 4)
	// 	printf("dst after%d: %s\n", i+1, dst+i);
	// printf("color : %d\n", *(unsigned int*)dst);
	}
}

void reset_all_puts(t_vars *vars)
{
	char	*dst;
	int x;
	int y;
	
	y = 0;
	while (y <= WINDOW_HEIGHT)
	{
		x = 0;
		while (x <= WINDOW_WIDTH)
		{
			dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
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

void free_map_list(t_map_list *map_list)
{
	t_map_list *tmp;
	while(map_list != NULL)
	{
		tmp = map_list->next;
		free(map_list);
		map_list = tmp;
	}
}

t_map_list *create_map_list(char *gnl)
{
	t_map_list *map_list;
	
	map_list = malloc(sizeof(t_map_list));
	if (map_list == NULL)
		exit(1);
	map_list->row = gnl;
	map_list->next = NULL;
	return (map_list);
}

t_map_list *read_file(char *filepath)
{
	int fd;
	char *gnl;
	t_map_list *prev;
	t_map_list *head;
	t_map_list *current;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit(1);
	gnl = get_next_line(fd);
	head = create_map_list(gnl);
	prev = head;
	while (1)
	{
		gnl = get_next_line(fd);
		if (gnl == NULL)
			break;
		current = create_map_list(gnl);
		prev->next = current;
		prev = current;
	}
	return (head);
}

int calc_height(t_map_list *head_map_list)
{
	int height;

	height = 0;
	while (head_map_list != NULL)
	{
		head_map_list = head_map_list->next;
		height++;
	}
	return (height);
}

int calc_width(t_map_list *head_map_list)
{
	int width;
	char **split;

	split = ft_split(head_map_list->row, ' ');
	width = 0;
	while (split[width] != NULL)
		width++;
	free_split(split);
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

int get_color(char *cell)
{
	char *color;

	color = ft_strchr(cell, ',');
	if (color != NULL)
	{
		// printf("color chr: %s\n", color+1);

		return (get_int_color_from_base16(color + 1));
	}
	return (0x00FFFFFF);
}

void make_map(t_map_list *head_map_list, t_vars *vars)
{
	char **split;
	int i;
	int j;
	
	t_map_list *tmp_list;
	tmp_list = head_map_list;
	vars->map = init_map_area(vars->height, vars->width);
	vars->map_color = init_map_area(vars->height, vars->width);
	i = 0;
	while (i < vars->height)
	{
		split = ft_split(tmp_list->row, ' ');
		j = 0;
		while (j < vars->width)
		{
			vars->map_color[i][j] = get_color(split[j]);
			vars->map[i][j] = ft_atoi(split[j]);
			j++;
		}
		free_split(split);
		tmp_list = tmp_list->next;
		i++;
	}
	// free_map_list(head_map_list);
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
	pos.x1_v = x1;
	pos.y1_v = y1;
	pos.x2_v = x2;
	pos.y2_v = y2;
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
			if (i + 1 < vars->height)
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
		vars->shift_y -= 20;
	if (keycode == XK_Down || keycode == XK_s)
		vars->shift_y += 20;
	if (keycode == XK_Right || keycode == XK_d)
		vars->shift_x += 20;
	if (keycode == XK_Left || keycode == XK_a)
		vars->shift_x -= 20;
	if (keycode == XK_i)
		vars->zoom += 0.1;
	if (keycode == XK_o)
		vars->zoom -= 0.1;
	if (keycode == XK_j)
		vars->zoom_z += 1;
	if (keycode == XK_k)
		vars->zoom_z -= 1;
	if (keycode == XK_n)
	{
		// TODO 一定以上でabortするの回避
		vars->angle = (vars->angle + 20 + 360) % 360;
		printf("angle %d\n", vars->angle);
	}
	if (keycode == XK_m)
	{
		// TODO 一定以上でabortするの回避
		vars->angle = (vars->angle - 20 + 360) % 360;
		printf("%d\n", vars->angle);

	}
	reset_all_puts(vars);
	draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

// void calc_center_after(int *x, int *y, t_vars *vars)
// {

// 	vars->x_center = (vars->x_center + vars->shift_x) / vars->zoom;
// 	vars->y_center = (vars->y_center + vars->shift_y) / vars->zoom;
// }
// {
// 	pos->x1_v = (pos->x1 * vars->base_zoom) * vars->zoom;
// }

void calc_center_default(t_vars *vars)
{
	int x_min;
	int x_max;
	int y_min;
	int y_max;

	// isometricで変換したときの最大最小の位置
	x_min =  (1 / sqrt(2)) * 0 - (1 / sqrt(2)) * vars->height;
	x_max =  (1 / sqrt(2)) * vars->width - (1 / sqrt(2)) * 0;
	y_min = 0;
	y_max = (1 / sqrt(6)) * vars->width + (1 / sqrt(6)) * vars->height - (2 / sqrt(6)) * vars->map[vars->height - 1][vars->width -1];
	// printf("x_min : %d\n", x_min);
	// printf("x_max : %d\n", x_max);
	// printf("y_min : %d\n", y_min);
	// printf("y_max : %d\n", y_max);

	int x_d;
	int y_d;
	// isometricの scale, translateする前の大きさ
	x_d = x_max - x_min;
	y_d = y_max - y_min;

	// printf("zoom_x : %d\n", WINDOW_WIDTH / x_d);
	// printf("zoom_y : %d\n", WINDOW_HEIGHT / y_d);
	if (WINDOW_WIDTH / x_d < WINDOW_HEIGHT / y_d)
		vars->base_zoom = WINDOW_WIDTH / x_d;
	else
		vars->base_zoom = WINDOW_HEIGHT / y_d;
	
	vars->x_center_isometric = (x_min + x_d / 2) * vars->base_zoom;
	vars->y_center_isometric = (y_min + y_d / 2) * vars->base_zoom;
	// printf("x_center : %d\n", x_center);
	// printf("y_center : %d\n", y_center);
	vars->shift_x = WINDOW_WIDTH / 2 - vars->x_center_isometric;
	vars->shift_y = WINDOW_HEIGHT / 2 - vars->y_center_isometric;
	// printf("shift_x : %d\n", vars->shift_x);
	// printf("shift_y : %d\n", vars->shift_y);
}

void calc_origin_center(t_vars *vars)
{
	vars->y_center = vars->height / 2;
	vars->x_center = vars->width / 2;
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q fdf");
}

int	main(int argc, char **argv)
{
	t_vars	*vars;
	t_map_list *head_map_list;


	if (argc != 2)
		exit(0);
	vars = malloc(sizeof(t_vars));
	if (vars == NULL)
		exit(1);
	head_map_list = read_file(argv[1]);
	vars->height = calc_height(head_map_list);
	vars->width = calc_width(head_map_list);
	calc_origin_center(vars);
	make_map(head_map_list, vars);
	free_map_list(head_map_list);

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world!");
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length,
								 &vars->endian);
	// my_mlx_pixel_put(&img, 10, 10, 0x0000FF00); // green
	// my_mlx_pixel_put(&img, 15, 15, 0x000000FF); // blue
	// my_mlx_pixel_put(&vars, 0, 0, 0x00FFFFFF); 
	// my_mlx_pixel_put(&vars, 5, 5, 0x00FF0000); // red

	calc_center_default(vars);

	vars->zoom = 1;
	vars->zoom_z = 1;
	vars->angle = 0;
	// vars->shift_x = 300;
	// vars->shift_y = 200;
	vars->color = create_trgb(0, 255, 255, 255);

	draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_key_hook(vars->win, catch_keycode, vars);
	mlx_hook(vars->win, DestroyNotify, StructureNotifyMask, close_by_red_btn, vars);
	// mlx_hook(vars->win, KeyPress, KeyPressMask, close_by_esc, &vars);
	mlx_loop(vars->mlx);
	return (0);
}
