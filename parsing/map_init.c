/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:05:41 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/10/11 13:56:06 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_validity(char *line)
{
	int	i;

	i = -1;
	while (line[++i] != '\0' && line[i] != '\n')
	{
		if (line[i] == '1' || line[i] == '0')
			return (1);
	}
	return (0);
}

void	check_empty_line(t_map *map)
{
	t_map	*tmp;
	int		i;
	int		flag;

	tmp = map;
	while (tmp)
	{
		flag = 0;
		i = -1;
		while (tmp->line[++i])
		{
			if (tmp->line[i] != ' ')
				flag++;
		}
		if (flag == 0)
			exit_error(ERR_MAP_INVALID);
		tmp = tmp->next;
	}
}

void	map_start(t_info *info)
{
	char	*line;

	while (READ_MAP)
	{
		line = get_next_line(info->fd);
		if (line == NO_MORE_TO_READ)
			exit_error(ERR_MAP_INVALID);
		if (check_validity(line))
		{
			info->map = malloc(sizeof(t_map));
			info->map->line = ft_linedup(line);
			info->map->prev = NULL;
			info->map->next = NULL;
			free(line);
			return ;
		}
		free(line);
	}
	exit_error(ERR_MAP_INVALID);
}

void	map_loop(t_map *cur, t_map *next, t_info *info)
{
	char	*line;
	int		width;

	while (READ_MAP)
	{
		line = get_next_line(info->fd);
		if (line == NO_MORE_TO_READ)
		{
			free(line);
			break ;
		}
		info->map_height++;
		width = ft_strlen(line) - 1;
		if (width > info->map_width)
			info->map_width = width;
		next = malloc(sizeof(t_map));
		next->line = ft_linedup(line);
		next->prev = cur;
		next->next = NULL;
		cur->next = next;
		cur = cur->next;
		next = next->next;
		free(line);
	}
}

void	map_init(t_info *info)
{
	t_map	*cur;
	t_map	*next;

	map_start(info);
	info->map_width = ft_strlen(info->map->line);
	info->map_height = 1;
	cur = info->map;
	next = info->map->next;
	map_loop(cur, next, info);
	check_empty_line(info->map);
}
