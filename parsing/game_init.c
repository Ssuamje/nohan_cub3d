/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:08:01 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/10/11 14:38:43 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_info_map(t_info *info)
{
	t_map	*tmp;

	tmp = info->map;
	while (tmp->next != NULL)
		tmp = tmp->next;
	while (tmp != NULL)
	{
		free(tmp->next);
		free(tmp->line);
		tmp = tmp->prev;
	}
	free(info->map);
}

int	is_nsew(char c)
{
	return (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

void	copy_map_loop(t_info *info, t_game *game, t_map *tmp, int i)
{
	int	j;
	int	tmp_len;

	j = -1;
	while (++j < info->map_width)
	{
		tmp_len = ft_strlen(tmp->line);
		if (j >= tmp_len || tmp->line[j] == '0' || tmp->line[j] == ' ')
			game->map[i][j] = 0;
		else if (tmp->line[j] == '1')
			game->map[i][j] = 1;
		else if (tmp->line[j] == 'N')
			game->map[i][j] = MAP_NORTH;
		else if (tmp->line[j] == 'S')
			game->map[i][j] = MAP_SOUTH;
		else if (tmp->line[j] == 'E')
			game->map[i][j] = MAP_EAST;
		else if (tmp->line[j] == 'W')
			game->map[i][j] = MAP_WEST;
		if (is_nsew(tmp->line[j]))
		{
			game->pos.x = i;
			game->pos.y = j;
		}
	}
}

void	copy_map(t_info	*info, t_game *game)
{
	int		i;
	t_map	*tmp;

	tmp = info->map;
	game->map = malloc(sizeof(int *) * info->map_height);
	i = -1;
	while (++i < info->map_height)
	{
		game->map[i] = malloc(sizeof(int) * info->map_width);
		copy_map_loop(info, game, tmp, i);
		tmp = tmp->next;
	}
	free_info_map(info);
	game->map_col = info->map_width;
	game->map_row = info->map_height;
}

void	copy_texture(t_info *info, t_game *game)
{
	game->texture[NORTH] = ft_linedup(info->north_path);
	free(info->north_path);
	game->texture[SOUTH] = ft_linedup(info->south_path);
	free(info->south_path);
	game->texture[EAST] = ft_linedup(info->east_path);
	free(info->east_path);
	game->texture[WEST] = ft_linedup(info->west_path);
	free(info->west_path);
}

void	init_map(t_info *info, t_game *game)
{
	copy_map(info, game);
	copy_texture(info, game);
	game->ceiling = rgb_to_hex(info->c_rgb[0], info->c_rgb[1], info->c_rgb[2]);
	game->floor = rgb_to_hex(info->f_rgb[0], info->f_rgb[1], info->f_rgb[2]);
	printf("%06X and %06X\n", game->ceiling, game->floor);
}
	// free(game->texture[NORTH]);
	// free(game->texture[SOUTH]);
	// free(game->texture[EAST]);
	// free(game->texture[WEST]);
	// for (int i = 0; i < game->map_col; i++)
	// 	free(game->map[i]);
	// free(game->map);