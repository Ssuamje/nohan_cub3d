#include "cub3d.h"

void	init_game_mlx(t_game *game);
void	print_game(t_game *game);
void	hook_key_events(t_game *game);
void	hook_key_events(t_game *game);
int		key_press(int key_code, t_game *game);
int		key_release(int key_code, t_game *game);
int		print_key_press(t_game *game);
void	init_game_keys(t_game *game);
int		run_game(t_game *game);
void	init_game_ray_condition(t_game *game);
void	init_game_textures(t_game *game);
void	print_int_map(t_game *game);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void    draw_vertical(t_game *game, int x);
void	clear_image(t_game *game);
void	raycast(t_game *game);
void	set_wall_texture(t_game *game);
void	set_colors(t_game *game);
int		read_keys_and_move(t_game *game);


void leaks()
{
	system("leaks cub3D");
}

/**
 * To-Do
 * 유효하지 않은 맵파일(없거나 권한이 없는, 열리지 않는), 유효하지 않은 확장자
 * 
*/

int main(int ac, char **av)
{
	t_info	info;
	t_game	game;
	
	atexit(leaks);
	if (ac != 2 || is_extension_valid(av[1]))
		exit_error(ERR_ARG);
	info_init(&info, av[1]);
	game_init(&info, &game);
	print_int_map(&game);
	init_game_mlx(&game);
	print_game(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	hook_key_events(&game);
	mlx_loop_hook(game.mlx, &run_game, &game);
	mlx_loop(game.mlx);
}

void	init_game_mlx(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img_data = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->img_line_size, &game->endian);
	init_game_keys(game);
	init_game_ray_condition(game);
	init_game_textures(game);
}
/**
 * img_ptr : 사용할 이미지를 지정한다
bits_per_pixel :  픽셀 색상을 나타내는데 필요한 비트 수
size_line : 이미지 한 줄을 메모리에 저장하는데 사용되는 바이트 수. 이 정보는 이미지의 한 줄에서 다른 줄로 이동하는 데 필요하다.
endian : 이미지의 픽셀 색상 저장 방식(little endian = 0, big endian = 1)
*/

void	init_game_textures(t_game *game)
{
	int dummy;
	game->texture_imgs[NORTH].img = mlx_xpm_file_to_image(game->mlx, game->texture[NORTH], &dummy, &dummy);
	game->texture_imgs[NORTH].data = mlx_get_data_addr(game->texture_imgs[NORTH].img, &game->texture_imgs[NORTH].bits_per_pixel, &game->texture_imgs[NORTH].line_length, &game->texture_imgs[NORTH].endian);
	game->texture_imgs[SOUTH].img = mlx_xpm_file_to_image(game->mlx, game->texture[SOUTH], &dummy, &dummy);
	game->texture_imgs[SOUTH].data = mlx_get_data_addr(game->texture_imgs[SOUTH].img, &game->texture_imgs[SOUTH].bits_per_pixel, &game->texture_imgs[SOUTH].line_length, &game->texture_imgs[SOUTH].endian);
	game->texture_imgs[WEST].img = mlx_xpm_file_to_image(game->mlx, game->texture[WEST], &dummy, &dummy);
	game->texture_imgs[WEST].data = mlx_get_data_addr(game->texture_imgs[WEST].img, &game->texture_imgs[WEST].bits_per_pixel, &game->texture_imgs[WEST].line_length, &game->texture_imgs[WEST].endian);
	game->texture_imgs[EAST].img = mlx_xpm_file_to_image(game->mlx, game->texture[EAST], &dummy, &dummy);
	game->texture_imgs[EAST].data = mlx_get_data_addr(game->texture_imgs[EAST].img, &game->texture_imgs[EAST].bits_per_pixel, &game->texture_imgs[EAST].line_length, &game->texture_imgs[EAST].endian);
}

void	init_game_ray_condition(t_game *game)
{
	//to-do : 맵에 따라 알맞게 설정하기
	game->dir.x = 1;
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
		exit(0);
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
	printf("RELEASED!\n");
	return (1);
}

int		run_game(t_game *game)
{
	read_keys_and_move(game);
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
		game->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		set_map_position(game);
		set_ray_direction(game);
		set_delta_distance(game);
		set_side_distance(game);
		dda(game);
		game->line_height = (int)(SCREEN_HEIGHT / game->perp_wall_dist);
		game->draw_start = -game->line_height / 2 + SCREEN_HEIGHT / 2;
		if (game->draw_start < 0)
			game->draw_start = 0;
		game->draw_end = game->line_height / 2 + SCREEN_HEIGHT / 2;
		if (game->draw_end >= SCREEN_HEIGHT)
			game->draw_end = SCREEN_HEIGHT - 1;
		set_wall_texture(game);
		set_colors(game);
		if (game->side == 1)
			game->color /= 2;
		draw_vertical(game, x);
		x++;
	}
}

int	read_keys_and_move(t_game *game)
{
	// printf("w = %d, s = %d, d = %d, a = %d, left = %d, right = %d\n", game->keys[W], game->keys[S], game->keys[D], game->keys[A], game->keys[LEFT], game->keys[RIGHT]);
	// printf("pos.x = %f, pos.y = %f, dir.x = %f, dir.y = %f, plane.x = %f, plane.y = %f\n", game->pos.x, game->pos.y, game->dir.x, game->dir.y, game->plane.x, game->plane.y);
	
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
	return (1);
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
	game->step.y = 1.0 * TEXTURE_HEIGHT / game->line_height; // step.y? step.x?
	game->texture_pos = (game->draw_start - SCREEN_HEIGHT / 2 + game->line_height / 2) * game->step.y;
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
	printf("map_row : %d\n", game->map_row);
	printf("map_col : %d\n", game->map_col);
	int i;
	int j;

	i = -1;
	while (++i < game->map_row)
	{
		j = -1;
		while (++j < game->map_col)
			printf("%d ", game->map[i][j]);
		printf("\n");
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
