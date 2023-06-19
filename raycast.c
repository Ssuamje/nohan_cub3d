/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:21:15 by sanan             #+#    #+#             */
/*   Updated: 2023/06/19 21:19:45 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define SCREEN_WIDTH 1980
#define SCREEN_HEIGHT 1060

int main() 
{
    t_vec   position; // 플레이어 맵 위치 벡터
    t_vec   direction; // 방향 벡터
    t_vec   plane; // 플레인 벡터
    void    *mlx;
    
    position.x = 22, position.y = 12;
    direction.x = -1, direction.y = 0;
    plane.x = 0, plane.y = 0.66;

    mlx = mlx_init();
    mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "큐브삼디");
    mlx_loop(mlx);
}