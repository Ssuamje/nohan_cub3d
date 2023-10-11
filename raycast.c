/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:21:15 by sanan             #+#    #+#             */
/*   Updated: 2023/06/23 15:15:45 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://lodev.org/cgtutor/raycasting.html#The_Basic_Idea_
#include "cub3d.h"
#define SCREEN_WIDTH 1980
#define SCREEN_HEIGHT 1060

int world_map[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,2,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,2,0,0,0,0,0,0,1},
    {1,0,0,0,0,2,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,2,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,2,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}};

int main() 
{
    void    *mlx;
    void    *win;
    mlx = mlx_init();
    win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "큐브삼디");
    raycast(mlx, win);
    mlx_loop(mlx);
    return (0);
}

void raycast() 
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
            if (world_map[(int)map.x][(int)map.y] > 0)
                hit = 1;
            
            if (side == 0)
                perp_wall_dist = (side_dist.x - delta_dist.y);
            else
                perp_wall_dist = (side_dist.y - delta_dist.x);
            
            int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

            int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
            if (draw_start < 0)
                draw_start = 0;
            int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
            if (draw_end >= SCREEN_HEIGHT)
                draw_end = SCREEN_HEIGHT - 1;

            int color = 0;
            if (world_map[(int)map.x][(int)map.y] == 1)
                color = 0xFF0000; // RED
            else if (world_map[(int)map.x][(int)map.y] == 2)
                color = 0x00FF00; // GREEN
            else if (world_map[(int)map.x][(int)map.y] == 3)
                color = 0x0000FF; // BLUE
            else if (world_map[(int)map.x][(int)map.y] == 4)
                color = 0xFFFFFF; // WHITE
            else
                color = 0xFFFF00; // YELLOW
            
            if (side == 1)
                color = color / 2;
            
            verLine(x, draw_start, draw_end, color);
        }
        fps.old_time = fps.curr_time;
        fps.curr_time = get_ticks();
        double frame_time = fps.curr_time - fps.old_time / 1000.0;
        printf("Frame Time : %f\n", frame_time);
        double move_speed = frame_time * 5.0;
        redraw(mlx, win, color);
        cls();
        readKeys(pos, dir, plane);
    }
}

//코파일럿
void readKeys(t_vec pos, t_vec dir, t_vec plane)
{
    int x = 0;
    int y = 0;
    int move_speed = 5;
    int rot_speed = 3;
    if (key_pressed(123))
    {
        // 왼쪽으로 회전
        double old_dir_x = dir.x;
        dir.x = dir.x * cos(rot_speed) - dir.y * sin(rot_speed);
        dir.y = old_dir_x * sin(rot_speed) + dir.y * cos(rot_speed);
        double old_plane_x = plane.x;
        plane.x = plane.x * cos(rot_speed) - plane.y * sin(rot_speed);
        plane.y = old_plane_x * sin(rot_speed) + plane.y * cos(rot_speed);
    }
    if (key_pressed(124))
    {
        // 오른쪽으로 회전
        double old_dir_x = dir.x;
        dir.x = dir.x * cos(-rot_speed) - dir.y * sin(-rot_speed);
        dir.y = old_dir_x * sin(-rot_speed) + dir.y * cos(-rot_speed);
        double old_plane_x = plane.x;
        plane.x = plane.x * cos(-rot_speed) - plane.y * sin(-rot_speed);
        plane.y = old_plane_x * sin(-rot_speed) + plane.y * cos(-rot_speed);
    }
    if (key_pressed(13))
    {
        // 앞으로 이동
        if (world_map[(int)(pos.x + dir.x * move_speed)][(int)pos.y] == 0)
            pos.x += dir.x * move_speed;
        if (world_map[(int)pos.x][(int)(pos.y + dir.y * move_speed)] == 0)
            pos.y += dir.y * move_speed;
    }
    if (key_pressed(1))
    {
        // 뒤로 이동
        if (world_map[(int)(pos.x - dir.x * move_speed)][(int)pos.y] == 0)
            pos.x -= dir.x * move_speed;
        if (world_map[(int)pos.x][(int)(pos.y - dir.y * move_speed)] == 0)
            pos.y -= dir.y * move_speed;
    }
}
/**
 * 위 코드 블록"if (key_pressed(123))"은 왼쪽 화살표 키가 눌렸을 때, 플레이어의 방향과 시야를 왼쪽으로 회전시키는 부분입니다. 해당 부분의 계산 과정과 이유를 설명해드리겠습니다.
old_dir_x 변수를 사용하여 현재 dir.x 값을 저장합니다. 이는 dir.x 값을 변경하기 전의 원래 값을 보존하기 위한 것입니다.
dir.x 값을 새로운 값으로 업데이트합니다. 회전 변환 행렬을 사용하여 dir.x와 dir.y 값을 새로운 회전된 값으로 계산합니다. 회전 변환 행렬은 2D 회전 변환을 수행하는 데 사용됩니다.
회전 변환 행렬을 사용하여 (dir.x, dir.y) 벡터를 rot_speed만큼의 각도로 시계 방향으로 회전시키면 다음과 같은 계산이 이루어집니다:
---
dir.x = dir.x * cos(rot_speed) - dir.y * sin(rot_speed);
dir.y = old_dir_x * sin(rot_speed) + dir.y * cos(rot_speed);
---
이를 통해 dir.x와 dir.y 값이 회전된 새로운 방향 벡터로 업데이트됩니다.
마찬가지로 old_plane_x 변수를 사용하여 현재 plane.x 값을 저장합니다. 이는 plane.x 값을 변경하기 전의 원래 값을 보존하기 위한 것입니다.
plane.x 값을 새로운 값으로 업데이트합니다. 방향 벡터와 마찬가지로 회전 변환 행렬을 사용하여 plane.x와 plane.y 값을 새로운 회전된 값으로 계산합니다.
---
plane.x = plane.x * cos(rot_speed) - plane.y * sin(rot_speed);
plane.y = old_plane_x * sin(rot_speed) + plane.y * cos(rot_speed);
---
이를 통해 plane.x와 plane.y 값이 회전된 새로운 시야 벡터로 업데이트됩니다.
결과적으로, 해당 코드 블록은 왼쪽 화살표 키가 눌리면 플레이어의 방향과 시야를 시계 방향으로 rot_speed만큼 회전시키는 것입니다. 이를 통해 플레이어는 왼쪽으로 회전한 상태에서 이동 및 시야를 조작할 수 있게 됩니다.
*/


//코파일럿
int key_pressed(int key)
{
    if (key == 123 || key == 124 || key == 13 || key == 1)
        return (1);
    return (0);
}

//코파일럿
void *my_mlx_init()
{
    void *mlx;
    mlx_init(mlx);
    mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "큐브삼디");
    mlx_loop(mlx);
    return (mlx);
}

void my_mlx_pixel_put(int x, int y, int color)
{
    char *dst;

    dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

//코파일럿
void    verLine(int x, int draw_start, int draw_end, int color)
{
    int y = 0;
    while (y < draw_start)
    {
        my_mlx_pixel_put(x, y, 0x000000);
        y++;
    }
    while (y < draw_end)
    {
        my_mlx_pixel_put(x, y, color);
        y++;
    }
    while (y < SCREEN_HEIGHT)
    {
        my_mlx_pixel_put(x, y, 0x000000);
        y++;
    }
}

//코파일럿
double get_ticks(void)
{
    struct timeval  time;
    double          sec;

    gettimeofday(&time, NULL);
    sec = (double)time.tv_sec;
    sec += (double)time.tv_usec / 1000000;
    return (sec);
}

//코파일럿
void redraw(void *mlx, void *win, int color)
{
    int x = 0;
    int y = 0;
    while (y < SCREEN_HEIGHT)
    {
        while (x < SCREEN_WIDTH)
        {
            mlx_pixel_put(mlx, win, x, y, color);
            x++;
        }
        x = 0;
        y++;
    }
}

//코파일럿, 배경 초기화하기
void cls(void)
{
    int x = 0;
    int y = 0;
    while (y < SCREEN_HEIGHT)
    {
        while (x < SCREEN_WIDTH)
        {
            my_mlx_pixel_put(x, y, 0x000000);
            x++;
        }
        x = 0;
        y++;
    }
}