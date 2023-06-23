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
int		run_game(t_game *game);
void	init_game_ray_condition(t_game *game);
void	print_int_map(t_game *game);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void    draw_vertical(t_game *game, int x);
void	clear_image(t_game *game);
void	raycast(t_game *game);
void	set_wall_texture(t_game *game);
void	set_colors(t_game *game);


void leaks()
{
	system("leaks cub3D");
}

int main(int ac, char **av)
{
	t_info	info;
	t_game	game;
	
	atexit(leaks);
	if (ac != 2 || is_extension_valid(av[1]))
		exit_error(ERR_ARG);
	info_init(&info, av[1]);
	game_init(&info, &game);
	// print_int_map(&game); <- segfault
	init_game_mlx(&game);
	print_game(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	hook_key_events(&game);
	mlx_loop_hook(game.mlx, &run_game, &game);
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
	init_game_ray_condition(game);
}
/**
 * img_ptr : 사용할 이미지를 지정한다
bits_per_pixel :  픽셀 색상을 나타내는데 필요한 비트 수
size_line : 이미지 한 줄을 메모리에 저장하는데 사용되는 바이트 수. 이 정보는 이미지의 한 줄에서 다른 줄로 이동하는 데 필요하다.
endian : 이미지의 픽셀 색상 저장 방식(little endian = 0, big endian = 1)
*/

void	init_game_ray_condition(t_game *game)
{
	//to-do : 맵에 따라 알맞게 설정하기
	game->pos.x = 3;
	game->pos.y = 3;
	game->dir.x = -1;
	game->dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0.66;
	game->side_dist.x = 0;
	game->side_dist.y = 0;
	game->delta_dist.x = 0;
	game->delta_dist.y = 0;
	game->step.x = 1;
	game->step.y = 1;
	game->fps.curr_time = 0;
	game->fps.old_time = 0;
}

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
	//print textures
	printf("north : %s\n", game->texture[NORTH]);
	printf("south : %s\n", game->texture[SOUTH]);
	printf("west : %s\n", game->texture[WEST]);
	printf("east : %s\n", game->texture[EAST]);
}

int		destory_game_mlx(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->img);
	free(game->mlx);
	return (1);
}

void	hook_key_events(t_game *game)
{
	mlx_hook(game->win, PRESS, MASK_PRESS, &key_press, game);
	mlx_hook(game->win, RELEASE, MASK_RELEASE, &key_release, game);
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
	printf("PRESSED!\n");
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
	printf("RELEASED!\n");
	return (1);
}

int		run_game(t_game *game)
{
	clear_image(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (1);
}

void	raycast(t_game *game)
{
	int x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		// calculate ray position and direction
		game->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		set_ray_direction(game);
		set_map_position(game);
		set_delta_distance(game);
		set_side_distance(game);
		// perform DDA
		dda(game);
		// calculate distance projected on camera direction
		if (game->side == 0)
			game->perp_wall_dist = (game->coord.x - game->pos.x + (1 - game->step.x) / 2) / game->ray_dir.x;
		else
			game->perp_wall_dist = (game->coord.y - game->pos.y + (1 - game->step.y) / 2) / game->ray_dir.y;
		// calculate height of line to draw on screen
		game->line_height = (int)(SCREEN_HEIGHT / game->perp_wall_dist);
		// calculate lowest and highest pixel to fill in current stripe
		game->draw_start = -game->line_height / 2 + SCREEN_HEIGHT / 2;
		if (game->draw_start < 0)
			game->draw_start = 0;
		game->draw_end = game->line_height / 2 + SCREEN_HEIGHT / 2;
		if (game->draw_end >= SCREEN_HEIGHT)
			game->draw_end = SCREEN_HEIGHT - 1;

		// // choose wall color 1
		// set_wall_texture(game);
		// if (game->map[(int)game->coord.x][(int)game->coord.y] == 1)
		// 	set_colors(game);
		// else
		// 	game->color = 0;
		
		// choose wall color 2
		if (game->map[(int)game->coord.x][(int)game->coord.y] == 1)
			game->color = 0xFFFF00;
		else if (game->map[(int)game->coord.x][(int)game->coord.y] == 2)
			game->color = 0x0000FF;
		else if (game->map[(int)game->coord.x][(int)game->coord.y] == 3)
			game->color = 0xFF0000;
		else if (game->map[(int)game->coord.x][(int)game->coord.y] == 4)
			game->color = 0x00FFFF;
		else
			game->color = 0xFFFFFF;

		// give x and y sides different brightness
		if (game->side == 1)
			game->color /= 2;
		// draw the pixels of the stripe as a vertical line
		draw_vertical(game, x);
		x++;
	}
}

void	read_keys_and_move(t_game *game)
{
	if (game->keys[W])
	{
		if (game->map[(int)(game->pos.x + game->dir.x * MOVE_SPEED)][(int)game->pos.y] == 0)
			game->pos.x += game->dir.x * MOVE_SPEED;
		if (game->map[(int)game->pos.x][(int)(game->pos.y + game->dir.y * MOVE_SPEED)] == 0)
			game->pos.y += game->dir.y * MOVE_SPEED;
	}
	if (game->keys[S])
	{
		if (game->map[(int)(game->pos.x - game->dir.x * MOVE_SPEED)][(int)game->pos.y] == 0)
			game->pos.x -= game->dir.x * MOVE_SPEED;
		if (game->map[(int)game->pos.x][(int)(game->pos.y - game->dir.y * MOVE_SPEED)] == 0)
			game->pos.y -= game->dir.y * MOVE_SPEED;
	}
	if (game->keys[D])
	{
		if (game->map[(int)(game->pos.x + game->dir.y * MOVE_SPEED)][(int)game->pos.y] == 0)
			game->pos.x += game->dir.y * MOVE_SPEED;
		if (game->map[(int)game->pos.x][(int)(game->pos.y - game->dir.x * MOVE_SPEED)] == 0)
			game->pos.y -= game->dir.x * MOVE_SPEED;
	}
	if (game->keys[A])
	{
		if (game->map[(int)(game->pos.x - game->dir.y * MOVE_SPEED)][(int)game->pos.y] == 0)
			game->pos.x -= game->dir.y * MOVE_SPEED;
		if (game->map[(int)game->pos.x][(int)(game->pos.y + game->dir.x * MOVE_SPEED)] == 0)
			game->pos.y += game->dir.x * MOVE_SPEED;
	}
	if (game->keys[LEFT])
	{
		// both camera direction and camera plane must be rotated
		double old_dir_x;
		double old_plane_x;
		old_dir_x = game->dir.x;
		game->dir.x = game->dir.x * cos(-ROTATE_SPEED) - game->dir.y * sin(-ROTATE_SPEED);
		game->dir.y = old_dir_x * sin(-ROTATE_SPEED) + game->dir.y * cos(-ROTATE_SPEED);
		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x * cos(-ROTATE_SPEED) - game->plane.y * sin(-ROTATE_SPEED);
		game->plane.y = old_plane_x * sin(-ROTATE_SPEED) + game->plane.y * cos(-ROTATE_SPEED);
	}
	if (game->keys[RIGHT])
	{
		// both camera direction and camera plane must be rotated
		double old_dir_x;
		double old_plane_x;
		old_dir_x = game->dir.x;
		game->dir.x = game->dir.x * cos(ROTATE_SPEED) - game->dir.y * sin(ROTATE_SPEED);
		game->dir.y = old_dir_x * sin(ROTATE_SPEED) + game->dir.y * cos(ROTATE_SPEED);
		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x * cos(ROTATE_SPEED) - game->plane.y * sin(ROTATE_SPEED);
		game->plane.y = old_plane_x * sin(ROTATE_SPEED) + game->plane.y * cos(ROTATE_SPEED);
	}
}

void	set_wall_texture(t_game *game)
{
	if (game->side == 0)
		game->wall_x = game->pos.y + game->perp_wall_dist * game->ray_dir.y;
	else
		game->wall_x = game->pos.x + game->perp_wall_dist * game->ray_dir.x;
	game->wall_x -= floor(game->wall_x);
	game->wall_texture_x = (int)(game->wall_x * (double)TEXTURE_WIDTH);
	if (game->side == 0 && game->ray_dir.x > 0)
		game->wall_texture_x = TEXTURE_WIDTH - game->wall_texture_x - 1;
	if (game->side == 1 && game->ray_dir.y < 0)
		game->wall_texture_x = TEXTURE_WIDTH - game->wall_texture_x - 1;
}

void	set_colors(t_game *game)
{
	if (game->side == 0 && game->ray_dir.x > 0)
		game->color = game->texture[EAST][TEXTURE_WIDTH * game->wall_texture_y + game->wall_texture_x];
	else if (game->side == 0 && game->ray_dir.x < 0)
		game->color = game->texture[WEST][TEXTURE_WIDTH * game->wall_texture_y + game->wall_texture_x];
	else if (game->side == 1 && game->ray_dir.y > 0)
		game->color = game->texture[SOUTH][TEXTURE_WIDTH * game->wall_texture_y + game->wall_texture_x];
	else
		game->color = game->texture[NORTH][TEXTURE_WIDTH * game->wall_texture_y + game->wall_texture_x];
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
	
	return (1);
}

void	print_int_map(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->map_row)
	{
		j = 0;
		while (j < game->map_col)
		{
			printf("%d ", game->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char *dst;

    dst = game->img_data + (y * game->img_line_size + x * (game->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void    draw_vertical(t_game *game, int x)
{
    int y = 0;
    while (y < game->draw_start)
    {
        my_mlx_pixel_put(game, x, y, game->ceiling);
        y++;
    }
    while (y < game->draw_end)
    {
        my_mlx_pixel_put(game, x, y, game->color);
        y++;
    }
    while (y < SCREEN_HEIGHT)
    {
        my_mlx_pixel_put(game, x, y, game->floor);
        y++;
    }
}

void	clear_image(t_game *game)
{
	int x;
	int y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(game, x, y, 0x000000);
			y++;
		}
		x++;
	}
}