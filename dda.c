/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:52:42 by sanan             #+#    #+#             */
/*   Updated: 2023/10/11 16:53:17 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(t_game *game)
{
	while (1)
	{
		if (game->side_dist.x < game->side_dist.y)
		{
			game->side_dist.x += game->delta_dist.x;
			game->coord.x += game->step.x;
			game->side = HORIZONTAL;
		}
		else
		{
			game->side_dist.y += game->delta_dist.y;
			game->coord.y += game->step.y;
			game->side = VERTICAL;
		}
		if (game->map[(int)game->coord.x][(int)game->coord.y])
			break ;
	}
	if (game->side == HORIZONTAL)
		game->perp_wall_dist = (game->side_dist.x - game->delta_dist.x);
	else
		game->perp_wall_dist = (game->side_dist.y - game->delta_dist.y);
}
