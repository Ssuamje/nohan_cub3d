/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:28:59 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/24 16:36:48 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_char(t_map *map)
{
	t_map	*tmp;
	int		i;
	int		player_cnt;

	tmp = map;
	player_cnt = 0;
	while (tmp)
	{
		i = -1;
		while (tmp->line[++i])
		{
			if (tmp->line[i] != 'N' && tmp->line[i] != 'S'
				&& tmp->line[i] != 'E' && tmp->line[i] != 'W'
				&& tmp->line[i] != '0' && tmp->line[i] != '1'
				&& tmp->line[i] != ' ')
				err_msg("error : invalid character");
			if (tmp->line[i] == 'N' || tmp->line[i] == 'S'
				|| tmp->line[i] == 'E' || tmp->line[i] == 'W')
				player_cnt += 1;
		}
		tmp = tmp->next;
	}
	if (player_cnt > 1)
		err_msg("error : more than one player");
	else if (player_cnt == 0)
		err_msg("error : player must exist");
}

void	info_init(t_info *info, char *filename)
{
	info->fd = open(filename, O_RDONLY);
	if (info->fd == OPEN_ERROR)
		err_msg("error : invalid map");
	elements_init(info);
	map_init(info);
	check_char(info->map);
	check_wall(info->map);
	close(info->fd);
}
