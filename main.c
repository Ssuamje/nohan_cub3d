/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:25:49 by hyungseok         #+#    #+#             */
/*   Updated: 2023/06/23 15:23:50 by hyungnoh         ###   ########.fr       */
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
	info_init(&info, &game, av[1]);
	// raycast(&info);
	return EXIT_SUCCESS;
}