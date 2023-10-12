/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:13:30 by sanan             #+#    #+#             */
/*   Updated: 2023/10/12 11:40:44 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * ray의 방향을 지정한다. camera_x는 상위 스코프에서 while로 -1 to 1까지이다.
 * dir.x, dir.y는 플레이어가 바라보는 방향(수직)이고, plane은 그에 대해 직교(수평)하는 벡터다.
 * 이를 통해 플레이어가 바라보는 한 방향(dir)에 따른 ray들을 하나하나 쏴보기 위한 방향을 재는 것이다.
*/
void	set_ray_direction(t_game *game)
{
	game->ray_dir.x = game->dir.x + game->plane.x * game->camera_x;
	game->ray_dir.y = game->dir.y + game->plane.y * game->camera_x;
}

/**
 * map에서 측정했을 때에, [x][y]인 플레이어의 좌표를 game_init에서 지정했다. (처음에는 정수임)
 * 이후에 런타임에서 사용자가 소수점의 단위로 움직일 수 있기 때문에, ray를 cast하는 고정된 위치로
 * (int)를 통해 내림하여 coord를 지정한다.
*/
void	set_map_position(t_game *game)
{
	game->coord.x = (int)game->pos.x;
	game->coord.y = (int)game->pos.y;
}

/**
 * 특정 유도식에 의거하여 다음 1칸으로 가기 위한 delta_dist를 현재 ray_dir를 기준으로 계산한다.
*/
void	set_delta_distance(t_game *game)
{
	game->delta_dist.x = fabs(1 / game->ray_dir.x);
	game->delta_dist.y = fabs(1 / game->ray_dir.y);
}

/**
 * ray_dir.x는 수직선을 기준으로 우측이면 양수, 좌측이면 음수다.
 * ray_dir.y는 수평선을 기준으로 위쪽이면 음수, 아래쪽이면 양수다.
 * step은 dda에서 ray_dir 부호에 따라 side_dist, delta_dist를 판별할 때 나아가는 방향이다.
 * delta_dist는 '1' 한 단위에 대한 다음 좌표까지의 거리이므로,
 * pos - coord를한 값을 delta_dist에 곱하면 현재 소수점인 좌표에서 다음 면까지의 거리를 나타낸다.
*/
void	set_side_distance(t_game *game)
{
	if (game->ray_dir.x < 0)
	{
		game->step.x = -1;
		game->side_dist.x = (game->pos.x - game->coord.x) * game->delta_dist.x;
	}
	else
	{
		game->step.x = 1;
		game->side_dist.x = (game->coord.x + 1.0 - game->pos.x) \
		* game->delta_dist.x;
	}
	if (game->ray_dir.y < 0)
	{
		game->step.y = -1;
		game->side_dist.y = (game->pos.y - game->coord.y) * game->delta_dist.y;
	}
	else
	{
		game->step.y = 1;
		game->side_dist.y = (game->coord.y + 1.0 - game->pos.y) \
		* game->delta_dist.y;
	}
}
