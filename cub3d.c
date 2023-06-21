/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:25:49 by hyungseok         #+#    #+#             */
/*   Updated: 2023/06/21 16:07:39 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 2 || is_extension_valid(av[1]))
		exit_error(ERR_ARG);
	info_init(&info, av[1]);
	printf("%d %d", info.map_height, info.map_width);
	// raycast(&info);
	return EXIT_SUCCESS;
}

	// printf("north path is: %s\n", info.north_path);
	// printf("south path is: %s\n", info.south_path);
	// printf("west path is: %s\n", info.west_path);
	// printf("east path is: %s\n", info.east_path);
	// printf("floor rgb is: %d,%d,%d\n", info.f_rgb[0], info.f_rgb[1], info.f_rgb[2]);
	// printf("ceiling rgb is: %d,%d,%d\n", info.c_rgb[0], info.c_rgb[1], info.c_rgb[2]);
	// printf("----------map----------\n");
	// while (info.map)
	// {
	// 	printf("%s\n", info.map->line);
	// 	info.map = info.map->next;
	// }
	// // atexit(leakss);