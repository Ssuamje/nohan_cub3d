/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:52:42 by sanan             #+#    #+#             */
/*   Updated: 2023/10/12 16:34:02 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * 면에 닿을 수 있는 최단 길이를 기준으로 계속 뻗어나가서, 해당하는 좌표계에 1이 있는지 확인한다.
 * 현재 좌표에서의 sx, sy를 측정하고, 이후에 dx, dy를 이용해서 한단위씩 넘어간다.
 * coord.x, coord.y가 맵의 [y][x]에 매핑되어있는 것 같지만, 실질적으로 좌표계를 기준으로 떠올렸을 때
 * [x][y]로 표현해서 계산할 수 있다.
*/
void	dda(t_game *game)
{
	while (1)
	{
		if (game->side_dist.x < game->side_dist.y)
		{
			game->side_dist.x += game->delta_dist.x;
			game->coord.x += game->step.x;
			game->side = 0;
		}
		else
		{
			game->side_dist.y += game->delta_dist.y;
			game->coord.y += game->step.y;
			game->side = 1;
		}
		if (game->map[(int)game->coord.x][(int)game->coord.y])
			break ;
	}
	if (game->side == 0)
		game->perp_wall_dist = (game->side_dist.x - game->delta_dist.x);
	else
		game->perp_wall_dist = (game->side_dist.y - game->delta_dist.y);
}
