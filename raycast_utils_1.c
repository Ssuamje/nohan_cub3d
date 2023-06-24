/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:13:30 by sanan             #+#    #+#             */
/*   Updated: 2023/06/24 09:50:21 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * 고정값 : camera_x <- -1, 1 사이의 double로, 스크린의 x좌표에 따라 달라짐
 * fps도 미리 만들어 놓고 연산하게 하면 됨. 
 * map 벡터의 경우 int로 설정.
*/

void    set_ray_direction(t_game *game)
{
    game->ray_dir.x = game->dir.x + game->plane.x * game->camera_x;
    game->ray_dir.y = game->dir.y + game->plane.y * game->camera_x;
}

void    set_map_position(t_game *game)
{
    game->coord.x = (int)game->pos.x;
    game->coord.y = (int)game->pos.y;
}

void    set_delta_distance(t_game *game)
{
    // game->delta_dist.x = ternary(game->ray_dir.x == 0, INT32_MAX, fabs(1 / game->ray_dir.x));
    // game->delta_dist.y = ternary(game->ray_dir.y == 0, INT32_MAX, fabs(1 / game->ray_dir.y));
    game->delta_dist.x = fabs(1 / game->ray_dir.x);
    game->delta_dist.y = fabs(1 / game->ray_dir.y);
}

int     ternary(int condition, int if_true, int if_false)
{
    if (condition)
        return (if_true);
    else
        return (if_false);
}

void    set_step(t_game *game)
{
    if (game->ray_dir.x < 0)
        game->step.x = -1;
    else
        game->step.x = 1;
    if (game->ray_dir.y < 0)
        game->step.y = -1;
    else
        game->step.y = 1;
}

void    set_side_distance(t_game *game)
{
    if (game->ray_dir.x < 0)
    {
        game->step.x = -1;
        game->side_dist.x = (game->pos.x - game->coord.x) * game->delta_dist.x;
    }
    else
    {
        game->step.x = 1;
        game->side_dist.x = (game->coord.x + 1.0 - game->pos.x) * game->delta_dist.x;
    }
    if (game->ray_dir.y < 0)
    {
        game->step.y = -1;
        game->side_dist.y = (game->pos.y - game->coord.y) * game->delta_dist.y;
    }
    else
    {
        game->step.y = 1;
        game->side_dist.y = (game->coord.y + 1.0 - game->pos.y) * game->delta_dist.y;
    }
}

void    dda(t_game *game)
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
        if (game->map[(int)game->coord.x][(int)game->coord.y] > 0)
            break;
    }

    if (game->side == 0)
        game->perp_wall_dist = ((game->side_dist.x - game->delta_dist.x) + (1 - game->step.x) / 2) / game->ray_dir.x;
        // game->perp_wall_dist = (game->side_dist.x - game->delta_dist.x);
        // game->perp_wall_dist = (game->side_dist.x - game->delta_dist.x) * game->ray_dir.x;
    else
        game->perp_wall_dist = ((game->side_dist.y - game->delta_dist.y) + (1 - game->step.y) / 2) / game->ray_dir.y;
        // game->perp_wall_dist = (game->side_dist.y - game->delta_dist.y);
        // game->perp_wall_dist = (game->side_dist.y - game->delta_dist.y) * game->ray_dir.y;
    
}

