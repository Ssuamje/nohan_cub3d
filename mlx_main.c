#include "cub3d.h"

void main()
{
	t_game	game;
	void	*mlx;
	void	*window;
	void	*image;

	mlx = mlx_init();
	window = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
	image = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void	init_game_mlx(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->data = (int *)mlx_get_data_addr(game->image, &game->bpp, &game->size_l, &game->endian);
}
