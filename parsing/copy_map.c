#include "../cub3d.h"

void	copy_map(t_info	*info)
{
	int		i;
	int		j;
	int		tmp_len;
	t_map	*tmp;

	i = -1;
	tmp = info->map;
	info->world_map = malloc(sizeof(int*) * info->map_height);
	while (++i < info->map_height)
	{
		j = -1;
		info->world_map[i] = malloc(sizeof(int) * info->map_width);
		tmp_len = ft_strlen(tmp->line);
		while (++j < info->map_width)
		{
			if (j >= tmp_len || tmp->line[j] == '0' || tmp->line[j] == ' ')
				info->world_map[i][j] = 0;
			else if (tmp->line[j] == '1')
				info->world_map[i][j] = 1;
			else if (tmp->line[j] == 'N')
				info->world_map[i][j] = 2;
			else if (tmp->line[j] == 'S')
				info->world_map[i][j] = 3;
			else if (tmp->line[j] == 'E')
				info->world_map[i][j] = 4;
			else if (tmp->line[j] == 'W')
				info->world_map[i][j] = 5;
		}
		tmp = tmp->next;
	}
}