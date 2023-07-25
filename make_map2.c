/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 02:32:58 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/26 02:33:19 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	calc_height(t_map_list *head_map_list)
{
	int	height;

	height = 0;
	while (head_map_list != NULL)
	{
		head_map_list = head_map_list->next;
		height++;
	}
	return (height);
}

int	calc_width(t_map_list *head_map_list)
{
	int		width;
	char	**split;

	split = ft_split(head_map_list->row, ' ');
	width = 0;
	while (split[width] != NULL)
		width++;
	free_split(split);
	return (width);
}

int	**init_map_area(int height, int width)
{
	int	**map;
	int	i;

	map = (int **)malloc(sizeof(int *) * height + 1);
	if (map == NULL)
		exit(1);
	i = 0;
	while (i < height)
	{
		map[i] = (int *)malloc(sizeof(int) * width + 1);
		if (map[i] == NULL)
			exit(1);
		i++;
	}
	return (map);
}

void	make_map(t_map_list *head_map_list, t_vars *vars)
{
	char		**split;
	int			i;
	int			j;
	t_map_list	*tmp_list;

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
}
