#include "cub3d.h"

void	init_game_mlx(t_game *game);
void	print_game(t_game *game);
int		destory_game_mlx(t_game *game);
void	hook_key_events(t_game *game);
void	hook_key_events(t_game *game);
int		key_press(int key_code, t_game *game);
int		key_release(int key_code, t_game *game);
int		print_key_press(t_game *game);
void	init_game_keys(t_game *game);

int main()
{
	t_game	game;
	
	init_game_mlx(&game);
	print_game(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	hook_key_events(&game);
	mlx_loop_hook(game.mlx, &print_key_press, &game);
	mlx_loop(game.mlx);
	destory_game_mlx(&game);
}

void	init_game_mlx(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img_data = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->img_line_size, &game->endian);
	init_game_keys(game);
}
/**
 * img_ptr : 사용할 이미지를 지정한다
bits_per_pixel :  픽셀 색상을 나타내는데 필요한 비트 수
size_line : 이미지 한 줄을 메모리에 저장하는데 사용되는 바이트 수. 이 정보는 이미지의 한 줄에서 다른 줄로 이동하는 데 필요하다.
endian : 이미지의 픽셀 색상 저장 방식(little endian = 0, big endian = 1)
*/

void	init_game_keys(t_game *game)
{
	game->keys[W] = 0;
	game->keys[S] = 0;
	game->keys[D] = 0;
	game->keys[A] = 0;
	game->keys[LEFT] = 0;
	game->keys[RIGHT] = 0;
	game->keys[ESC] = 0;
}

void	print_game(t_game *game)
{
	printf("mlx : %p\n", game->mlx);
	printf("win : %p\n", game->win);
	printf("img : %p\n", game->img);
	printf("img_data : %p\n", game->img_data);
	printf("bits_per_pixel : %d\n", game->bits_per_pixel);
	printf("img_line_size : %d\n", game->img_line_size);
	printf("endian : %d\n", game->endian);
}

int		destory_game_mlx(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_window(game->mlx, game->win);
	free(game->mlx);
	return (1);
}

void	hook_key_events(t_game *game)
{
	mlx_hook(game->win, PRESS, 1L<<0, &key_press, game);
	mlx_hook(game->win, RELEASE, 1L<<1, &key_release, game);
}

int		key_press(int key_code, t_game *game)
{
	if (key_code == KEY_W)
		game->keys[W] = 1;
	else if (key_code == KEY_S)
		game->keys[S] = 1;
	else if (key_code == KEY_D)
		game->keys[D] = 1;
	else if (key_code == KEY_A)
		game->keys[A] = 1;
	else if (key_code == KEY_LEFT)
		game->keys[LEFT] = 1;
	else if (key_code == KEY_RIGHT)
		game->keys[RIGHT] = 1;
	else if (key_code == KEY_ESC)
	{
		destory_game_mlx(game);
		exit(0);
	}
	return (1);
}

int		key_release(int key_code, t_game *game)
{
	if (key_code == KEY_W)
		game->keys[W] = 0;
	else if (key_code == KEY_S)
		game->keys[S] = 0;
	else if (key_code == KEY_D)
		game->keys[D] = 0;
	else if (key_code == KEY_A)
		game->keys[A] = 0;
	else if (key_code == KEY_LEFT)
		game->keys[LEFT] = 0;
	else if (key_code == KEY_RIGHT)
		game->keys[RIGHT] = 0;
	else if (key_code == KEY_ESC)
		game->keys[ESC] = 0;
	return (1);
}

int		print_key_press(t_game *game)
{
	if (game->keys[W])
		printf("W\n");
	else if (game->keys[S])
		printf("S\n");
	else if (game->keys[D])
		printf("D\n");
	else if (game->keys[A])
		printf("A\n");
	else if (game->keys[LEFT])
		printf("LEFT\n");
	else if (game->keys[RIGHT])
		printf("RIGHT\n");
	else if (game->keys[ESC])
		printf("ESC\n");
	return (1);
}