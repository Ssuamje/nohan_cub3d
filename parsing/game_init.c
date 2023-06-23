#include "../cub3d.h"

int	rgb_to_hex(int red, int green, int blue) {
    return (red << 16) | (green << 8) | blue;
}

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

void	copy_map(t_info	*info, t_game *game)
{
	int		i;
	int		j;
	int		tmp_len;
	t_map	*tmp;

	tmp = info->map;
	game->map = malloc(sizeof(int*) * info->map_height);
	i = -1;
	while (++i < info->map_height)
	{
		j = -1;
		game->map[i] = malloc(sizeof(int) * info->map_width);
		tmp_len = ft_strlen(tmp->line);
		while (++j < info->map_width)
		{
			if (j >= tmp_len || tmp->line[j] == '0' || tmp->line[j] == ' ')
				game->map[i][j] = 0;
			else if (tmp->line[j] == '1')
				game->map[i][j] = 1;
			else if (tmp->line[j] == 'N')
				game->map[i][j] = 2;
			else if (tmp->line[j] == 'S')
				game->map[i][j] = 3;
			else if (tmp->line[j] == 'E')
				game->map[i][j] = 4;
			else if (tmp->line[j] == 'W')
				game->map[i][j] = 5;
		}
		tmp = tmp->next;
	}
	free_info_map(info);
	game->map_col = info->map_height;
	game->map_row = info->map_width;
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

void	game_init(t_info *info, t_game *game)
{
	copy_map(info, game);
	copy_texture(info, game);
	game->ceiling = rgb_to_hex(info->c_rgb[0],info->c_rgb[1],info->c_rgb[2]);
	game->floor = rgb_to_hex(info->f_rgb[0],info->f_rgb[1],info->f_rgb[2]);
	printf("%06X and %06X", game->ceiling, game->floor);

}
	// free(game->texture[NORTH]);
	// free(game->texture[SOUTH]);
	// free(game->texture[EAST]);
	// free(game->texture[WEST]);
	// for (int i = 0; i < game->map_col; i++)
	// 	free(game->map[i]);
	// free(game->map);