/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:00:22 by sanan             #+#    #+#             */
/*   Updated: 2023/10/11 14:57:26 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_back_and_forth(t_game *game)
{
	if (game->keys[W])
	{
		if (game->map[(int)(game->pos.x + game->dir.x * MOVE_SPEED)] \
		[(int)game->pos.y] == 0)
			game->pos.x += game->dir.x * MOVE_SPEED;
		if (game->map[(int)game->pos.x] \
		[(int)(game->pos.y + game->dir.y * MOVE_SPEED)] == 0)
			game->pos.y += game->dir.y * MOVE_SPEED;
	}
	if (game->keys[S])
	{
		if (game->map[(int)(game->pos.x - game->dir.x * MOVE_SPEED)] \
		[(int)game->pos.y] == 0)
			game->pos.x -= game->dir.x * MOVE_SPEED;
		if (game->map[(int)game->pos.x] \
		[(int)(game->pos.y - game->dir.y * MOVE_SPEED)] == 0)
			game->pos.y -= game->dir.y * MOVE_SPEED;
	}
}

void	move_side_to_side(t_game *game)
{
	if (game->keys[D])
	{
		if (game->map[(int)(game->pos.x + game->dir.y * MOVE_SPEED)] \
		[(int)game->pos.y] == 0)
			game->pos.x += game->dir.y * MOVE_SPEED;
		if (game->map[(int)game->pos.x] \
		[(int)(game->pos.y - game->dir.x * MOVE_SPEED)] == 0)
			game->pos.y -= game->dir.x * MOVE_SPEED;
	}
	if (game->keys[A])
	{
		if (game->map[(int)(game->pos.x - game->dir.y * MOVE_SPEED)] \
		[(int)game->pos.y] == 0)
			game->pos.x -= game->dir.y * MOVE_SPEED;
		if (game->map[(int)game->pos.x] \
		[(int)(game->pos.y + game->dir.x * MOVE_SPEED)] == 0)
			game->pos.y += game->dir.x * MOVE_SPEED;
	}
}

void	move_head_to_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (game->keys[RIGHT])
	{
		old_dir_x = game->dir.x;
		game->dir.x = game->dir.x * cos(-ROTATE_SPEED) - \
		game->dir.y * sin(-ROTATE_SPEED);
		game->dir.y = old_dir_x * sin(-ROTATE_SPEED) + \
		game->dir.y * cos(-ROTATE_SPEED);
		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x * cos(-ROTATE_SPEED) - \
		game->plane.y * sin(-ROTATE_SPEED);
		game->plane.y = old_plane_x * sin(-ROTATE_SPEED) + \
		game->plane.y * cos(-ROTATE_SPEED);
	}
}

void	move_head_to_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (game->keys[LEFT])
	{
		old_dir_x = game->dir.x;
		game->dir.x = game->dir.x * cos(ROTATE_SPEED) - \
		game->dir.y * sin(ROTATE_SPEED);
		game->dir.y = old_dir_x * sin(ROTATE_SPEED) + \
		game->dir.y * cos(ROTATE_SPEED);
		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x * cos(ROTATE_SPEED) - \
		game->plane.y * sin(ROTATE_SPEED);
		game->plane.y = old_plane_x * sin(ROTATE_SPEED) + \
		game->plane.y * cos(ROTATE_SPEED);
	}
}

int	read_keys_and_move(t_game *game)
{
	if (game->keys[W] || game->keys[S])
		move_back_and_forth(game);
	if (game->keys[D] || game->keys[A])
		move_side_to_side(game);
	if (game->keys[RIGHT])
		move_head_to_right(game);
	if (game->keys[LEFT])
		move_head_to_left(game);
	return (1);
}
