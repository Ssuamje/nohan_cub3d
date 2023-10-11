/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:04:33 by sanan             #+#    #+#             */
/*   Updated: 2023/10/11 17:36:34 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_buffer_to_image(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			put_pixel(game, x, y, game->draw_buffer[y][x]);
			y++;
		}
		x++;
	}
}

void	set_draw_buffer(t_game *game, int x)
{
	int	y;

	y = -1;
	while (++y < game->draw_start)
		game->draw_buffer[y][x] = game->ceiling;
	while (y < game->draw_end)
	{
		game->wall_texture_y = (int)game->texture_pos;
		game->texture_pos += game->step_texture;
		if (game->side == VERTICAL && game->ray_dir.x > 0)
			game->color = get_color(game, NORTH);
		if (game->side == VERTICAL && game->ray_dir.x < 0)
			game->color = get_color(game, SOUTH);
		if (game->side == HORIZONTAL && game->ray_dir.y > 0)
			game->color = get_color(game, WEST);
		if (game->side == HORIZONTAL && game->ray_dir.y < 0)
			game->color = get_color(game, EAST);
		game->draw_buffer[y][x] = game->color;
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		game->draw_buffer[y][x] = game->floor;
		y++;
	}
}

unsigned int	get_color(t_game *game, int direction)
{
	int				x;
	int				y;
	unsigned int	color;
	t_img			tex;

	x = game->wall_texture_x;
	y = game->wall_texture_y;
	tex = game->texture_imgs[direction];
	color = *(unsigned int *) \
	(tex.data + (y * tex.line_length + x * (tex.bits_per_pixel / 8)));
	return (color);
}

void	calculate_texture(t_game *game)
{
	if (game->side == VERTICAL)
		game->wall_x = game->pos.y + game->perp_wall_dist * game->ray_dir.y;
	else
		game->wall_x = game->pos.x + game->perp_wall_dist * game->ray_dir.x;
	game->wall_x -= floor(game->wall_x);
	game->wall_texture_x = (int)(game->wall_x * (double)TEXTURE_WIDTH);
	if ((game->side == VERTICAL && game->ray_dir.x > 0)
	|| (game->side == HORIZONTAL && game->ray_dir.y < 0))
		game->wall_texture_x = TEXTURE_WIDTH - game->wall_texture_x - 1;
	game->step_texture = 1.0 * TEXTURE_HEIGHT / game->line_height;
	game->texture_pos = (game->draw_start - SCREEN_HEIGHT / 2 + game->line_height / 2) * game->step_texture;
}
