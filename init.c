/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:32:07 by sanan             #+#    #+#             */
/*   Updated: 2023/06/25 22:07:47 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_mlx(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img_data = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->img_line_size, &game->endian);
	init_game_ray_condition(game);
	init_game_textures(game);
}

void	init_game_textures(t_game *game)
{
	set_img_file_and_data(game, NORTH);
	set_img_file_and_data(game, SOUTH);
	set_img_file_and_data(game, WEST);
	set_img_file_and_data(game, EAST);
}

void	set_img_file_and_data(t_game *game, int direction)
{
	int dummy;
	t_img *tex;

	tex = &game->texture_imgs[direction];
	tex->img = mlx_xpm_file_to_image(game->mlx,\
		game->texture[direction], &dummy, &dummy);
	tex->data = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,\
		 &tex->line_length, &tex->endian);
}

void	init_game_ray_condition(t_game *game)
{
	game->dir.x = 0;
	game->dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0;
	set_player_direction(game, game->map[(int)game->pos.x][(int)game->pos.y]);
	game->map[(int)game->pos.x][(int)game->pos.y] = 0;
	game->side_dist.x = 0;
	game->side_dist.y = 0;
	game->delta_dist.x = 0;
	game->delta_dist.y = 0;
	game->step.x = 1;
	game->step.y = 1;
}

void	set_player_direction(t_game *game, int direction)
{
	if (direction == MAP_NORTH)
	{
		game->dir.x = -1;
		game->plane.y = 0.66;
	}
	else if (direction == MAP_SOUTH)
	{
		game->dir.x = 1;
		game->plane.y = -0.66;
	}
	else if (direction == MAP_EAST)
	{
		game->dir.y = 1;
		game->plane.x = 0.66;
	}
	else if (direction == MAP_WEST)
	{
		game->dir.y = -1;
		game->plane.x = -0.66;
	}
	game->pos.x += 0.5;
	game->pos.y += 0.5;
}