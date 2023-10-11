/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:25:49 by hyungseok         #+#    #+#             */
/*   Updated: 2023/10/11 13:05:13 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leakss()
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_info	info;
	t_game	game;

	if (ac != 2 || is_extension_valid(av[1]))
		exit_error(ERR_ARG);
	info_init(&info, av[1]);
	game_init(&info, &game);
	raycast(&info);
	atexit(leakss);
	return EXIT_SUCCESS;
}
