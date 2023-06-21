#include "cub3d.h"

void	raycast(t_info *info)
{
	t_vec   position; // 플레이어 맵 위치 벡터
    t_vec   direction; // 방향 벡터
    t_vec   plane; // 플레인 벡터
	t_fps	fps;
    void    *mlx;

	(void)info;
	position.x = 22, position.y = 12;
    direction.x = -1, direction.y = 0;
    plane.x = 0, plane.y = 0.66;
	fps.current = 0, fps.past = 0;

    mlx = mlx_init();
    mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
    mlx_loop(mlx);
}