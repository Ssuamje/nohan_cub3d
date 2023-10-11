/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:49:40 by sanan             #+#    #+#             */
/*   Updated: 2023/10/11 14:59:32 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# define OPEN_ERROR -1
# define READ_ELEMENTS 1
# define READ_MAP 1
# define FILLED 1
# define UNFILLED 0
# define NO_MORE_TO_READ NULL

# define MOVE_SPEED 0.025
# define ROTATE_SPEED 0.02

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 640
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 480
# endif
# ifndef GAME_NAME
#  define GAME_NAME "cub3D"
# endif
# ifndef TEXTURE_WIDTH
#  define TEXTURE_WIDTH 242
# endif
# ifndef TEXTURE_HEIGHT
#  define TEXTURE_HEIGHT 242
# endif

enum	e_errno{
	ERR_ELEM_INVALID,
	ERR_ELEM_LACK,
	ERR_MAP_FILE,
	ERR_MAP_INVALID,
	ERR_MAP_INVALID_PLAYER,
	ERR_ARG,
	ERR_WALL_INVALID,
};

enum	e_key
{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_ESC = 53,
};

enum	e_key_indexes
{
	W = 0,
	A,
	S,
	D,
	LEFT,
	RIGHT,
	ESC,
};

typedef struct s_map
{
	char			*line;
	struct s_map	*prev;
	struct s_map	*next;
}	t_map;

enum e_direction
{
	NORTH = 0,
	SOUTH,
	EAST,
	WEST,
	MAP_NORTH = 2,
	MAP_SOUTH = 3,
	MAP_EAST = 4,
	MAP_WEST = 5,
};

enum e_key_events
{
	PRESS = 2,
	RELEASE = 3,
	EXIT = 17,
};

enum e_key_masks
{
	MASK_PRESS = 1L<<0,
	MASK_RELEASE = 1L<<1,
	MASK_EXIT = 1L<<17,
};

typedef struct s_info
{
	int				fd;
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	int				f_rgb[3];
	int				c_rgb[3];
	struct s_map	*map;
	int				map_width;
	int				map_height;
}	t_info;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_img
{
	void	*img;
	void	*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*img_data;
	int				bits_per_pixel;
	int				img_line_size;
	int				endian;
	char			*texture[4];
	t_img			texture_imgs[4];
	int				**map;
	int				map_row;
	int				map_col;
	int				ceiling;
	int				floor;
	int				keys[7];
	t_vec			pos;
	t_vec			coord;
	t_vec			dir;
	t_vec			old_dir;
	t_vec			ray_dir;
	t_vec			plane;
	double			camera_x;
	t_vec			side_dist;
	t_vec			delta_dist;
	double			perp_wall_dist;
	t_vec			step;
	int				color;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				wall_texture_x;
	int				wall_texture_y;
	double			wall_x;
	double			step_texture;
	double			texture_pos;
	int				draw_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
}	t_game;

/* ./cub3d_utils.c */

int				is_extension_valid(char *filename);
int				elements_filled(int elements_cnt[]);
void			check_comma(char *str);
void			check_file_order(char *line);
int				get_last(t_map *map);

char			*ft_linedup(char *s1);
char			**ft_split(char const *s, char c);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
int				ft_atoi(const char *str);
int				ft_strcmp(char *s1, char *s2);

/* ./cub3d_utils2.c */
int				rgb_to_hex(int red, int green, int blue);
int				is_nsew(char c);

/* ./parsing/check_island_utils.c */
void			check_island1(char **board, t_map *tmp, int *x, int *y);
void			check_island2(char **board, int last);

/* ./parsing/elements_init.c */

void			elements_cnt_init(int elements_cnt[]);
void			check_path(t_info *info, char *line, int elements_cnt[]);
void			check_f_rgb(t_info *info, char *line, int elements_cnt[]);
void			check_c_rgb(t_info *info, char *line, int elements_cnt[]);
void			elements_init(t_info *info);

/* ./parsing/check_wall.c */

void			check_side(t_map *map, int i, int j, int last);
void			check_closed(t_map *map, int i, int j, int last);
void			recursion(char **board, int x, int y, int last);
void			check_island(t_map *map, int i, int last);
void			check_wall(t_map *map);

/* ./parsing/info_init.c */

void			check_char(t_map *map, int player_cnt);
void			info_init(t_info *info, char *filename);

/* ./parsing/map_init.c */

int				check_validity(char *line);
void			check_empty_line(t_map *map);
void			map_start(t_info *info);
void			map_init(t_info *info);

/* ./parsing/game_init.c */
void			free_info_map(t_info *info);
void			copy_map(t_info	*info, t_game *game);
void			copy_texture(t_info *info, t_game *game);
void			init_map(t_info *info, t_game *game);

/* ./get_next_line/get_next_line_utils.c */

size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(char *s1);

/* ./get_next_line/get_next_line.c */

char			*get_next_line(int fd);

/* ./error/exit_error.c */

char			*get_msg_by_errno(int errno);
void			exit_error(int errno);

void			set_ray_direction(t_game *game);
void			set_player_direction(t_game *game, int direction);
void			set_map_position(t_game *game);
void			set_delta_distance(t_game *game);
void			set_step(t_game *game);
void			set_side_distance(t_game *game);
void			dda(t_game *game);

void			init_game_mlx(t_game *game);
void			init_game_textures(t_game *game);
void			init_game_ray_condition(t_game *game);
void			set_img_file_and_data(t_game *game, int direction);

int				key_press(int key_code, t_game *game);
int				key_release(int key_code, t_game *game);

void			put_pixel(t_game *game, int x, int y, int color);
unsigned int	get_color(t_game *game, int direction);
void			hook_key_events(t_game *game);
int				run_game(t_game *game);
void			put_pixel(t_game *game, int x, int y, int color);
void			draw_vertical(t_game *game, int x);
void			raycast(t_game *game);
int				read_keys_and_move(t_game *game);
void			set_draw_range(t_game *game);
void			calculate_texture(t_game *game);
void			set_draw_buffer(t_game *game, int x);
void			put_buffer_to_image(t_game *game);
unsigned int	get_color(t_game *game, int direction);

#endif