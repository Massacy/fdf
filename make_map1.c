/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 02:26:57 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/26 02:34:52 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_map_list	*create_map_list(char *gnl)
{
	t_map_list	*map_list;

	map_list = malloc(sizeof(t_map_list));
	if (map_list == NULL)
		exit(1);
	map_list->row = gnl;
	map_list->next = NULL;
	return (map_list);
}

static void	free_map_list(t_map_list *map_list)
{
	t_map_list	*tmp;

	while (map_list != NULL)
	{
		tmp = map_list->next;
		free(map_list);
		map_list = tmp;
	}
}

static t_map_list	*read_file(char *filepath)
{
	int			fd;
	char		*gnl;
	t_map_list	*prev;
	t_map_list	*head;
	t_map_list	*current;

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
			break ;
		current = create_map_list(gnl);
		prev->next = current;
		prev = current;
	}
	return (head);
}

void	prepare_map(char *filepath, t_vars *vars)
{
	t_map_list	*head_map_list;

	head_map_list = read_file(filepath);
	vars->height = calc_height(head_map_list);
	vars->width = calc_width(head_map_list);
	calc_origin_center(vars);
	make_map(head_map_list, vars);
	free_map_list(head_map_list);
}
