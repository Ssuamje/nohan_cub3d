/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:25:49 by hyungseok         #+#    #+#             */
/*   Updated: 2023/03/06 15:25:55 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leakss(void)
{
	system("leaks a.out");
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 2 || check_arg(av[1]))
		err_msg("error : improper arguments");
	info_init(&info, av[1]);
	printf("north path is: %s\n", info.north_path);
	printf("south path is: %s\n", info.south_path);
	printf("west path is: %s\n", info.west_path);
	printf("east path is: %s\n", info.east_path);
	printf("floor rgb is: %d,%d,%d\n", info.f_rgb[0], info.f_rgb[1], info.f_rgb[2]);
	printf("ceiling rgb is: %d,%d,%d\n", info.c_rgb[0], info.c_rgb[1], info.c_rgb[2]);
	printf("----------map----------\n");
	while (info.map)
	{
		printf("%s\n", info.map->line);
		info.map = info.map->next;
	}
	// atexit(leakss);
	return (EXIT_SUCCESS);
}
