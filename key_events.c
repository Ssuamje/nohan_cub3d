/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:59:42 by sanan             #+#    #+#             */
/*   Updated: 2023/10/23 18:39:57 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hook_key_events(t_game *game)
{
	mlx_hook(game->win, PRESS, MASK_PRESS, &key_press, game);
	mlx_hook(game->win, RELEASE, MASK_RELEASE, &key_release, game);
	mlx_hook(game->win, RED_X_BUTTON, MASK_EXIT, &exit_game, game);
}

int	key_press(int key_code, t_game *game)
{
	if (key_code == KEY_W)
		game->keys[W] = 1;
	else if (key_code == KEY_S)
		game->keys[S] = 1;
	else if (key_code == KEY_D)
		game->keys[D] = 1;
	else if (key_code == KEY_A)
		game->keys[A] = 1;
	else if (key_code == KEY_LEFT)
		game->keys[LEFT] = 1;
	else if (key_code == KEY_RIGHT)
		game->keys[RIGHT] = 1;
	else if (key_code == KEY_ESC)
		exit(0);
	return (1);
}

int	key_release(int key_code, t_game *game)
{
	if (key_code == KEY_W)
		game->keys[W] = 0;
	else if (key_code == KEY_S)
		game->keys[S] = 0;
	else if (key_code == KEY_D)
		game->keys[D] = 0;
	else if (key_code == KEY_A)
		game->keys[A] = 0;
	else if (key_code == KEY_LEFT)
		game->keys[LEFT] = 0;
	else if (key_code == KEY_RIGHT)
		game->keys[RIGHT] = 0;
	return (1);
}

int exit_game(void) {
	exit(0);
}
