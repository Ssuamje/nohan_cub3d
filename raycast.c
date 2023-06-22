/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:21:15 by sanan             #+#    #+#             */
/*   Updated: 2023/06/20 09:00:05 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define SCREEN_WIDTH 1980
#define SCREEN_HEIGHT 1060

int main() 
{
    // void    *mlx;

    // mlx = mlx_init();
    // mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "큐브삼디");
    // mlx_loop(mlx);
    t_vec   pos; // 플레이어 맵 위치 벡터
    t_vec   dir; // 방향 벡터
    t_vec   plane; // 플레인 벡터
    t_fps   fps;
    
    pos.x = 22, pos.y = 12;
    dir.x = -1, dir.y = 0;
    plane.x = 0, plane.y = 0.66;
    fps.curr_time = 0;
    fps.old_time = 0;
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        double camera_x = (2 * x / (double)SCREEN_WIDTH) - 1;
        t_vec   ray_dir;
        ray_dir.x = dir.x + plane.x * camera_x;
        ray_dir.y = dir.y + plane.y * camera_x;


        t_vec   map;
        t_vec   side_dist;
        t_vec   delta_dist;
        t_vec   step;
        double perp_wall_dist;

        // 좌표(플레이어가 위치한 박스) 지정
        map.x = (int)pos.x;
        map.y = (int)pos.y;

        delta_dist.x = ray_dir.x == 0 ? INT64_MAX : abs(1/ ray_dir.x);
        delta_dist.y = ray_dir.y == 0 ? INT64_MAX : abs(1/ ray_dir.y);

        int hit = 0;
        int side;

        // 바라보는 방향에 따른 step 및 side_dist 설정
        if (ray_dir.x < 0)
        {
            step.x = -1;
            side_dist.x = (pos.x - map.x) * delta_dist.x;
        }
        else
        {
            step.x = 1;
            side_dist.x = (map.x + 1.0 - pos.x) * delta_dist.x;
        }
        if (ray_dir.y < 0)
        {
            step.y = -1;
            side_dist.y = (pos.y - map.y) * delta_dist.y;
        }
        else
        {
            step.y = 1;
            side_dist.y = (map.y + 1.0 - pos.y) * delta_dist.y;
        }

        while (hit == 0)
        {
            if (side_dist.x < side_dist.y)
            {
                side_dist.x += delta_dist.x;
                map.x += step.x;
                side = 0;
            }
            else
            {
                side_dist.y += delta_dist.y;
                map.y += step.y;
                side = 1;
            }
            if (worldMap[map.x][map.y] > 0)
                hit = 1;
        }
    }
}