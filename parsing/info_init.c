/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:28:59 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/10/11 13:48:23 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_char(t_map *map, int player_cnt)
{
	t_map	*tmp;
	int		i;

	tmp = map;
	while (tmp)
	{
		i = -1;
		while (tmp->line[++i])
		{
			if (tmp->line[i] != 'N' && tmp->line[i] != 'S'
				&& tmp->line[i] != 'E' && tmp->line[i] != 'W'
				&& tmp->line[i] != '0' && tmp->line[i] != '1'
				&& tmp->line[i] != ' ')
				exit_error(ERR_MAP_FILE);
			if (tmp->line[i] == 'N' || tmp->line[i] == 'S'
				|| tmp->line[i] == 'E' || tmp->line[i] == 'W')
				player_cnt += 1;
		}
		tmp = tmp->next;
	}
	if (player_cnt > 1)
		exit_error(ERR_MAP_INVALID_PLAYER);
	else if (player_cnt == 0)
		exit_error(ERR_MAP_INVALID_PLAYER);
}

void	info_init(t_info *info, char *filename)
{
	info->fd = open(filename, O_RDONLY);
	if (info->fd == OPEN_ERROR)
		exit_error(ERR_MAP_FILE);
	elements_init(info);
	map_init(info);
	check_char(info->map, 0);
	check_wall(info->map);
	close(info->fd);
}
