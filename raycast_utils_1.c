/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:13:30 by sanan             #+#    #+#             */
/*   Updated: 2023/06/23 15:07:15 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * 고정값 : camera_x <- -1, 1 사이의 double로, 스크린의 x좌표에 따라 달라짐
 * fps도 미리 만들어 놓고 연산하게 하면 됨. 
 * map 벡터의 경우 int로 설정.
*/

void    set_ray_direction(t_vec *ray_dir, t_vec dir, t_vec plane, double camera_x)
{
    ray_dir->x = dir.x + plane.x * camera_x;
    ray_dir->y = dir.y + plane.y * camera_x;
}

void    set_map_position(t_vec *map, t_vec pos)
{
    map->x = (int)pos.x;
    map->y = (int)pos.y;
}

void    set_delta_distance(t_vec *delta_dist, t_vec ray_dir)
{
    delta_dist->x = fabs(1 / ray_dir.x);
    delta_dist->y = fabs(1 / ray_dir.y);
}

void    set_step(t_vec *step, t_vec ray_dir)
{
    if (ray_dir.x < 0)
        step->x = -1;
    else
        step->x = 1;
    if (ray_dir.y < 0)
        step->y = -1;
    else
        step->y = 1;
}

void    set_side_distance(t_vec *side_dist, t_vec ray_dir, t_vec pos, t_vec map)
{
    if (ray_dir.x < 0)
        side_dist->x = (pos.x - map.x) * side_dist->x;
    else
        side_dist->x = (map.x + 1.0 - pos.x) * side_dist->x;
    if (ray_dir.y < 0)
        side_dist->y = (pos.y - map.y) * side_dist->y;
    else
        side_dist->y = (map.y + 1.0 - pos.y) * side_dist->y;
}

void    dda(int **world_map, t_vec  *pos, t_vec *ray_dir,
 t_vec *side_dist, t_vec *delta_dist, t_vec *step, t_vec *map)
{
    int hit = 0;
    int side = 0;
    while (!hit)
    {
        if (side_dist->x < side_dist->y)
        {
            side_dist->x += delta_dist->x;
            map->x += step->x;
            side = 0;
        }
        else
        {
            side_dist->y += delta_dist->y;
            map->y += step->y;
            side = 1;
        }
        if (world_map[(int)map->x][(int)map->y] > 0)
            break;
    }

    double perpendicular_wall_distance;
    if (side == 0)
        perpendicular_wall_distance = (side_dist->x - delta_dist->x) * ray_dir->x;
    else
        perpendicular_wall_distance = (side_dist->y - delta_dist->y) * ray_dir->y;
    
}

