/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:05:47 by sanan             #+#    #+#             */
/*   Updated: 2023/10/11 14:06:06 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_draw_range(t_game *game)
{
	game->line_height = (int)(SCREEN_HEIGHT / game->perp_wall_dist);
	game->draw_start = -game->line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->draw_start < 0)
		game->draw_start = 0;
	game->draw_end = game->line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->draw_end >= SCREEN_HEIGHT)
		game->draw_end = SCREEN_HEIGHT - 1;
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->img_data + (y * game->img_line_size + \
	x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_vertical(t_game *game, int x)
{
	int	y;

	y = 0;
	while (y < game->draw_start)
	{
		put_pixel(game, x, y, game->ceiling);
		y++;
	}
	while (y < game->draw_end)
	{
		put_pixel(game, x, y, game->color);
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		put_pixel(game, x, y, game->floor);
		y++;
	}
}