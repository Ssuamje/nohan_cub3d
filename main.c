/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:42:17 by sanan             #+#    #+#             */
/*   Updated: 2023/10/11 14:43:59 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_info	info;
	t_game	game;

	if (ac != 2 || is_extension_valid(av[1]))
		exit_error(ERR_ARG);
	info_init(&info, av[1]);
	init_map(&info, &game);
	init_game_mlx(&game);
	printf("texture[NORTH] = %s\n", game.texture[NORTH]);
	printf("texture[SOUTH] = %s\n", game.texture[SOUTH]);
	printf("texture[WEST] = %s\n", game.texture[WEST]);
	printf("texture[EAST] = %s\n", game.texture[EAST]);
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	hook_key_events(&game);
	mlx_loop_hook(game.mlx, &run_game, &game);
	mlx_loop(game.mlx);
}

int	run_game(t_game *game)
{
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	read_keys_and_move(game);
	return (1);
}

void	raycast(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		game->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		set_ray_direction(game);
		set_map_position(game);
		set_delta_distance(game);
		set_side_distance(game);
		dda(game);
		set_draw_range(game);
		calculate_texture(game);
		set_draw_buffer(game, x);
		x++;
	}
	put_buffer_to_image(game);
}
