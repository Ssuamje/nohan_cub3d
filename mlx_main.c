#include "cub3d.h"

void	init_game_mlx(t_game *game);
void	hook_key_events(t_game *game);
void	hook_key_events(t_game *game);
int		key_press(int key_code, t_game *game);
int		key_release(int key_code, t_game *game);
int		print_key_press(t_game *game);
int		run_game(t_game *game);
void	init_game_ray_condition(t_game *game);
void	init_game_textures(t_game *game);
void	print_int_map(t_game *game);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void    draw_vertical(t_game *game, int x);
void	raycast(t_game *game);
int		read_keys_and_move(t_game *game);
void	set_draw_range(t_game *game);
void	calculate_texture(t_game *game);
void	set_draw_buffer(t_game *game, int x);
void	put_buffer_to_image(t_game *game);
unsigned int	get_color(t_game *game, int direction);

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
	init_map(&info, &game);
	init_game_mlx(&game);
	printf("texture[NORTH] = %s\n", game.texture[NORTH]);
	printf("texture[SOUTH] = %s\n", game.texture[SOUTH]);
	printf("texture[WEST] = %s\n", game.texture[WEST]);
	printf("texture[EAST] = %s\n", game.texture[EAST]);
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	hook_key_events(&game);
	mlx_loop_hook(game.mlx, &run_game, &game);
	mlx_loop(game.mlx);
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
	return (1);
}

int		run_game(t_game *game)
{
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	read_keys_and_move(game);
	return (1);
}

void	raycast(t_game *game)
{
	int x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		game->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		set_ray_direction(game);
		set_map_position(game);
		set_delta_distance(game);
		set_side_distance(game);
		dda(game);
		set_draw_range(game);
		calculate_texture(game);
		set_draw_buffer(game, x);
		x++;
	}
	put_buffer_to_image(game);
}

void	put_buffer_to_image(t_game *game)
{
	int x;
	int y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(game, x, y, game->draw_buffer[y][x]);
			y++;
		}
		x++;
	}
}

void	set_draw_buffer(t_game *game, int x)
{
	int y;

	y = 0;
	while (y < game->draw_start)
	{
		game->draw_buffer[y][x] = game->ceiling;
		y++;
	}
	while (y < game->draw_end)
	{
		game->wall_texture_y = (int)game->texture_pos;
		game->texture_pos += game->step_texture;
		if (game->side == 0 && game->ray_dir.x > 0)
			game->color = get_color(game, NORTH);
		if (game->side == 0 && game->ray_dir.x < 0)
			game->color = get_color(game, SOUTH);
		if (game->side == 1 && game->ray_dir.y > 0)
			game->color = get_color(game, WEST);
		if (game->side == 1 && game->ray_dir.y < 0)
			game->color = get_color(game, EAST);
		game->draw_buffer[y][x] = game->color;
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		game->draw_buffer[y][x] = game->floor;
		y++;
	}
}

unsigned int	get_color(t_game *game, int direction)
{
	int x;
	int y;
	unsigned int color;
	t_img	tex;

	x = game->wall_texture_x;
	y = game->wall_texture_y;
	tex = game->texture_imgs[direction];
	color = *(unsigned int *)(tex.data + (y * tex.line_length + x * (tex.bits_per_pixel / 8)));
	// if (game->side == 1)
		// color = (color >> 1) & 8355711;
	return (color);
}

void	calculate_texture(t_game *game)
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
	game->step_texture = 1.0 * TEXTURE_HEIGHT / game->line_height;
	game->texture_pos = (game->draw_start - SCREEN_HEIGHT / 2 + game->line_height / 2) * game->step_texture;
}

void	set_draw_range(t_game *game)
{
	game->line_height = (int)(SCREEN_HEIGHT / game->perp_wall_dist);
	game->draw_start = -game->line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->draw_start < 0)
		game->draw_start = 0;
	game->draw_end = game->line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->draw_end >= SCREEN_HEIGHT)
		game->draw_end = SCREEN_HEIGHT - 1;
}

int	read_keys_and_move(t_game *game)
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
	if (game->keys[RIGHT])
	{
		double old_dir_x;
		double old_plane_x;
		old_dir_x = game->dir.x;
		game->dir.x = game->dir.x * cos(-ROTATE_SPEED) - game->dir.y * sin(-ROTATE_SPEED);
		game->dir.y = old_dir_x * sin(-ROTATE_SPEED) + game->dir.y * cos(-ROTATE_SPEED);
		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x * cos(-ROTATE_SPEED) - game->plane.y * sin(-ROTATE_SPEED);
		game->plane.y = old_plane_x * sin(-ROTATE_SPEED) + game->plane.y * cos(-ROTATE_SPEED);
	}
	if (game->keys[LEFT])
	{
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
